// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/IDetector2D.h
//! @brief     Defines interface IDetector2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IDETECTOR2D_H_
#define IDETECTOR2D_H_

#include "Types.h"
#include "IParameterized.h"
#include "EigenCore.h"
#include "IPixelMap.h"
#include "IDetectorResolution.h"
#include "DetectorMask.h"
#include "SimulationElement.h"
#include "Beam.h"

#include <boost/scoped_ptr.hpp>

//! @class IDetector
//! @ingroup simulation
//! @brief The detector interface.

class BA_CORE_API_ IDetector2D : public IParameterized
{
public:
    IDetector2D();
    IDetector2D(const IDetector2D& other);

    virtual IDetector2D* clone() const=0;

    virtual ~IDetector2D() {}

    void addAxis(const IAxis &axis)
    {
        m_axes.push_back(axis.clone());
    }

    const IAxis &getAxis(size_t index) const;

    size_t getDimension() const
    {
        return m_axes.size();
    }

    void clear()
    {
        m_axes.clear();
    }

    //! Sets detector parameters using axes of output data
    void matchDetectorAxes(const OutputData<double> &output_data);

    //! Sets detector parameters using angle ranges
    void setDetectorParameters(size_t n_x, double x_min, double x_max,
                               size_t n_y, double y_min, double y_max);

    //! Sets detector parameters using axes
    void setDetectorAxes(const IAxis &axis0, const IAxis &axis1);

    //! Sets the detector resolution
    void setDetectorResolution(IDetectorResolution *p_detector_resolution)
    {
        if (mP_detector_resolution.get()!=p_detector_resolution) {
            mP_detector_resolution.reset(p_detector_resolution);
        }
    }

    //! Applies the detector resolution to the given intensity maps
    void applyDetectorResolution(OutputData<double> *p_intensity_map) const;

    const IDetectorResolution *getDetectorResolutionFunction() const
    {
        return mP_detector_resolution.get();
    }

    //! Sets the polarization analyzer characteristics of the detector
    void setAnalyzerProperties(const kvector_t &direction, double efficiency,
                               double total_transmission=1.0);

#ifndef GCCXML_SKIP_THIS
    //! Gets the polarization density matrix (in spin basis along z-axis)
    Eigen::Matrix2cd getAnalyzerOperator() const
    {
        return m_analyzer_operator;
    }
#endif

    //! Adds parameters from local pool to external pool and call recursion over direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                    int copy_number = -1) const;

    //! Normalize intensity data with detector cell sizes.
    void normalize(OutputData<double> *p_data, double sin_alpha_i) const;


    //! removes all masks from the detector
    void removeMasks();

    //! Adds mask of given shape to the stack of detector masks. The mask value 'true' means
    //! that the channel will be excluded from the simulation. The mask which is added last
    //! has priority.
    //! @param shape The shape of mask (Rectangle, Polygon, Line, Ellipse)
    //! @mask_value The value of mask
    void addMask(const Geometry::IShape2D &shape, bool mask_value = true);

    //! Put the mask for all detector channels (i.e. exclude whole detector from the analysis)
    void maskAll();

    const DetectorMask *getDetectorMask() const;

    bool isMasked(size_t index) const;

    //! return true if has masks
    bool hasMasks() const;

#ifndef GCCXML_SKIP_THIS
    //! Create a vector of SimulationElement objects according to the detector and its mask
    std::vector<SimulationElement> createSimulationElements(const Beam& beam);
#endif

protected:
    //! Create an IPixelMap for the given OutputData object and index
    virtual IPixelMap* createPixelMap(size_t index) const=0;

    //! Registers some class members for later access via parameter pool.
    virtual void init_parameters() {}

    //! Generates an axis with correct name and default binning for given index
    virtual IAxis* createAxis(size_t index, size_t n_bins, double min, double max) const=0;

    //! Returns the name for the axis with given index
    virtual std::string getAxisName(size_t index) const=0;

    bool isCorrectAxisIndex(size_t index) const
    {
        return index < getDimension();
    }

    //! Checks if data has a compatible format with the detector.
    bool dataShapeMatches(const OutputData<double> *p_data) const;

    //! Returns the solid angle for the given data element
    double getSolidAngle(size_t index) const;

    //! Initialize polarization (for constructors)
    void initPolarizationOperator();

    //! Calculate axis index for given global index
    size_t getAxisBinIndex(size_t index, size_t selected_axis) const;

    //! swap function
    void swapContent(IDetector2D &other);

    SafePointerVector<IAxis> m_axes;
    boost::scoped_ptr<IDetectorResolution> mP_detector_resolution;
#ifndef GCCXML_SKIP_THIS
    Eigen::Matrix2cd m_analyzer_operator; //!< polarization analyzer operator
#endif
    DetectorMask m_detector_mask;

private:
    //! Verify if the given analyzer properties are physical
    bool checkAnalyzerProperties(const kvector_t &direction, double efficiency,
                                 double total_transmission) const;

#ifndef GCCXML_SKIP_THIS
    Eigen::Matrix2cd calculateAnalyzerOperator(const kvector_t &direction, double efficiency,
                                               double total_transmission = 1.0) const;
#endif
};

#endif /* IDETECTOR2D_H_ */