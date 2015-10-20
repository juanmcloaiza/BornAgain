// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/IDetector2D.cpp
//! @brief     Implements shared functionality of interface IDetector2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IDetector2D.h"
#include "MessageService.h"
#include "BornAgainNamespace.h"
#include "Rectangle.h"

#include <Eigen/LU>
#include <boost/scoped_ptr.hpp>

IDetector2D::IDetector2D()
    : m_axes()
{
    init_parameters();
    initPolarizationOperator();
}

IDetector2D::IDetector2D(const IDetector2D &other)
    : IParameterized(), m_axes(other.m_axes),
      m_analyzer_operator(other.m_analyzer_operator), m_detector_mask(other.m_detector_mask)
{
    setName(other.getName());
    if (other.mP_detector_resolution.get())
        mP_detector_resolution.reset(other.mP_detector_resolution->clone());
    init_parameters();
}

const IAxis &IDetector2D::getAxis(size_t index) const
{
    if (isCorrectAxisIndex(index)) {
        return *m_axes[index];
    }
    throw OutOfBoundsException("Not so many axes in this detector.");
}

void IDetector2D::matchDetectorAxes(const OutputData<double> &output_data)
{
    if (output_data.getRank()!=2) {
        throw LogicErrorException(
            "IDetector2D::matchDetectorAxes() -> Error! Data is not two dimensional");
    }
    clear();
    for (size_t i_axis = 0; i_axis < output_data.getRank(); ++i_axis) {
        const IAxis* p_axis = output_data.getAxis(i_axis)->clone();
        addAxis(*p_axis);
    }
}

void IDetector2D::setDetectorParameters(size_t n_x, double x_min, double x_max,
                                        size_t n_y, double y_min, double y_max)
{
    clear();
    boost::scoped_ptr<IAxis> P_axis0(createAxis(0, n_x, x_min, x_max));
    boost::scoped_ptr<IAxis> P_axis1(createAxis(1, n_y, y_min, y_max));
    addAxis(*P_axis0);
    addAxis(*P_axis1);
}

void IDetector2D::setDetectorAxes(const IAxis &axis0, const IAxis &axis1)
{
    clear();
    addAxis(axis0);
    addAxis(axis1);
}

void IDetector2D::applyDetectorResolution(OutputData<double> *p_intensity_map) const
{
    if (!p_intensity_map) {
        throw NullPointerException("IDetector2D::applyDetectorResolution() -> "
                                   "Error! Null pointer to intensity map");
    }
    if (mP_detector_resolution.get()) {
        mP_detector_resolution->applyDetectorResolution(p_intensity_map);
    } else {
        msglog(MSG::WARNING) << "IDetector2D::applyDetectorResolution() -> "
                                "No detector resolution function found";
    }
}

void IDetector2D::setAnalyzerProperties(const kvector_t &direction, double efficiency,
                                     double total_transmission)
{
    if (!checkAnalyzerProperties(direction, efficiency, total_transmission)) {
        throw Exceptions::ClassInitializationException(
            "IDetector2D::setAnalyzerProperties: the given properties are not physical");
    }
    m_analyzer_operator = calculateAnalyzerOperator(direction, efficiency, total_transmission);
}


std::string IDetector2D::addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                  int copy_number) const
{
    // add own parameters
    std::string new_path
        = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the resolution function
    if (mP_detector_resolution) {
        mP_detector_resolution->addParametersToExternalPool(new_path, external_pool, -1);
    }
    return new_path;
}

void IDetector2D::normalize(OutputData<double> *p_data, double sin_alpha_i) const
{
    // if shapes do not match, do nothing
    if (!dataShapeMatches(p_data))
        return;

    // if not a 2d detector, do nothing
    if (p_data->getRank() != 2)
        return;

    // This normalization assumes that the intensity map contains
    // total differential scattering cross sections
    // (as opposed to the usual cross section per scattering particle)
    for (OutputData<double>::iterator it = p_data->begin(); it != p_data->end(); ++it) {
        double factor = getSolidAngle(it.getIndex()) / sin_alpha_i;
        (*it) *= factor;
    }
}

void IDetector2D::removeMasks()
{
    m_detector_mask.removeMasks();
}

void IDetector2D::addMask(const Geometry::IShape2D &shape, bool mask_value)
{
    m_detector_mask.addMask(shape, mask_value);
    m_detector_mask.initMaskData(*this);
}

void IDetector2D::maskAll()
{
    if(m_axes.size() != 2) return;

    m_detector_mask.removeMasks();

    Geometry::Rectangle rect(m_axes[0]->getMin(), m_axes[1]->getMin(), m_axes[0]->getMax(), m_axes[1]->getMax());
    addMask(rect, true);
}

const DetectorMask *IDetector2D::getDetectorMask() const
{
    return &m_detector_mask;
}

bool IDetector2D::isMasked(size_t index) const
{
    if(!m_detector_mask.getMaskData()->isInitialized()) return false;
    return m_detector_mask.getMask(index);
}

bool IDetector2D::hasMasks() const
{
    return m_detector_mask.hasMasks();
}

std::vector<SimulationElement> IDetector2D::createSimulationElements(const Beam &beam)
{
    std::vector<SimulationElement> result;
    double wavelength = beam.getWavelength();
    double alpha_i = - beam.getAlpha();  // Defined to be always positive in Beam
    double phi_i = beam.getPhi();
    Eigen::Matrix2cd beam_polarization = beam.getPolarization();
    Eigen::Matrix2cd analyzer_operator = getAnalyzerOperator();

    if (getDimension()!=2) {
        throw RuntimeErrorException("IDetector2D::createSimulationElements: "
                                    "detector is not two-dimensional");
    }
    if (!hasMasks()) m_detector_mask.initMaskData(*this);
    const OutputData<bool>* mask_data = m_detector_mask.getMaskData();
    for (size_t index=0; index<mask_data->getAllocatedSize(); ++index) {
        if ((*mask_data)[index]) continue;
        boost::scoped_ptr<IPixelMap> P_pixel_map(createPixelMap(index));
        SimulationElement sim_element(wavelength, alpha_i, phi_i, P_pixel_map.get());
        sim_element.setPolarization(beam_polarization);
        sim_element.setAnalyzerOperator(analyzer_operator);
        result.push_back(sim_element);
    }
    return result;
}

bool IDetector2D::dataShapeMatches(const OutputData<double> *p_data) const
{
    if (p_data->getRank() != getDimension())
        return false;
    for (size_t i = 0; i < getDimension(); ++i) {
        const IAxis *p_data_axis = p_data->getAxis(i);
        const IAxis &detector_axis = getAxis(i);
        if (detector_axis != *p_data_axis)
            return false;
    }
    return true;
}

double IDetector2D::getSolidAngle(size_t index) const
{
    boost::scoped_ptr<IPixelMap> P_pixel_map(createPixelMap(index));
    return P_pixel_map->getSolidAngle();
}

void IDetector2D::initPolarizationOperator()
{
    m_analyzer_operator = Eigen::Matrix2cd::Identity();
}

size_t IDetector2D::getAxisBinIndex(size_t index, size_t selected_axis) const
{
    size_t remainder(index);
    for (size_t i=0; i<getDimension(); ++i)
    {
        size_t i_axis = getDimension()-1-i;
        int result = remainder % m_axes[i_axis]->getSize();
        if(selected_axis == i_axis ) return result;
        remainder /= m_axes[i_axis]->getSize();
    }
    throw LogicErrorException("IDetector2D::getAxisBinIndex() -> "
                              "Error! No axis with given number");
}

void IDetector2D::swapContent(IDetector2D &other)
{
    std::swap(this->m_axes, other.m_axes);
    boost::swap(this->mP_detector_resolution, other.mP_detector_resolution);
    std::swap(this->m_analyzer_operator, other.m_analyzer_operator);
    std::swap(this->m_detector_mask, other.m_detector_mask);
}

bool IDetector2D::checkAnalyzerProperties(const kvector_t &direction, double efficiency,
                                       double total_transmission) const
{
    if (direction.mag() == 0.0)
        return false;
    double aplus = total_transmission * (1.0 + efficiency);
    double amin = total_transmission * (1.0 - efficiency);
    if (aplus < 0.0 || aplus > 1.0)
        return false;
    if (amin < 0.0 || amin > 1.0)
        return false;
    return true;
}

Eigen::Matrix2cd IDetector2D::calculateAnalyzerOperator(const kvector_t &direction, double efficiency,
                                                     double total_transmission) const
{
    Eigen::Matrix2cd result;
    double x = direction.x()/direction.mag();
    double y = direction.y()/direction.mag();
    double z = direction.z()/direction.mag();
    double sum = total_transmission * 2.0;
    double diff = total_transmission * efficiency * 2.0;
    complex_t im(0.0, 1.0);
    result(0, 0) = (sum + diff*z) / 2.0;
    result(0, 1) = diff*(x - im * y) / 2.0;
    result(1, 0) = diff*(x + im * y) / 2.0;
    result(1, 1) = (sum - diff*z) / 2.0;
    return result;
}
