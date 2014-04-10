// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/IIntensityNormalizer.cpp
//! @brief     Implements class IntensityNormalizer.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IIntensityNormalizer.h"
#include <algorithm>
#include <iostream>

void IntensityNormalizer::init_parameters()
{
    clearParameterPool();
    registerParameter("scale", &m_scale);
    registerParameter("shift", &m_shift);
}

IntensityNormalizer *IntensityNormalizer::clone() const
{
    IntensityNormalizer *result = new IntensityNormalizer(m_scale, m_shift);
    result->setMaximumIntensity(m_max_intensity);
    result->setName(getName());
    return result;
}

OutputData<double> *IntensityNormalizer::createNormalizedData(
        const OutputData<double>& data) const
{
    double factor = m_max_intensity;
    if(factor == 0) {
        // using self maximum amplitude for normalization
        OutputData<double>::const_iterator it = std::max_element(data.begin(), data.end());
        factor = *it;
    }
    if(factor == 0)
        throw DivisionByZeroException(
                "IntensityNormalizer::createNormalizedData() -> "
                "Error! Maximum intensity is 0.");
    OutputData<double > *normalized_data = data.clone();
    for(OutputData<double >::iterator it =
            normalized_data->begin(); it!=normalized_data->end(); ++it) {
        double value = (*it);
        (*it) = m_scale*(value/factor) + m_shift;
    }
    return normalized_data;
}

