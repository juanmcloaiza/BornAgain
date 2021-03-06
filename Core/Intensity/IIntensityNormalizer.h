// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Intensity/IIntensityNormalizer.h
//! @brief     Defines classes IOutputDataNormalizer,
//!              OutputDataNormalizer, OutputDataSimpleNormalizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INTENSITY_IINTENSITYNORMALIZER_H
#define BORNAGAIN_CORE_INTENSITY_IINTENSITYNORMALIZER_H

#include "Core/Basics/ICloneable.h"
#include "Core/Intensity/OutputData.h"
#include "Core/Parametrization/INode.h"

//! Interface to OutputData normalizers.
//! @ingroup algorithms_internal

class BA_CORE_API_ IIntensityNormalizer : public ICloneable, public INode
{
public:
    virtual ~IIntensityNormalizer() {}

    virtual IIntensityNormalizer* clone() const = 0;

    virtual OutputData<double>* createNormalizedData(const OutputData<double>& data) const = 0;

    virtual void apply(OutputData<double>& data) const = 0;

    virtual void setMaximumIntensity(double) = 0;
};

//! Standard OutputData normalizer, with configurable max_intensity.
//! @ingroup algorithms_internal

class BA_CORE_API_ IntensityNormalizer : public IIntensityNormalizer
{
public:
    IntensityNormalizer(double scale = 1.0, double shift = 0.0)
        : m_scale(scale), m_shift(shift), m_max_intensity(0.0)
    {
        setName("Normalizer");
        init_parameters();
    }

    virtual ~IntensityNormalizer() {}

    virtual IntensityNormalizer* clone() const;

    void accept(INodeVisitor* visitor) const { visitor->visit(this); }

    virtual OutputData<double>* createNormalizedData(const OutputData<double>& data) const;

    void apply(OutputData<double>& data) const final;

    virtual void setMaximumIntensity(double max_intensity) { m_max_intensity = max_intensity; }

protected:
    //! Registers some class members for later access via parameter pool
    void init_parameters();

    double m_scale;
    double m_shift;
    double m_max_intensity;
};

//! Simplified OutputData normalizer, with max_intensity=1.
//! @ingroup algorithms_internal

class BA_CORE_API_ IntensityScaleAndShiftNormalizer : public IntensityNormalizer
{
public:
    IntensityScaleAndShiftNormalizer(double scale = 1.0, double shift = 0.0)
        : IntensityNormalizer(scale, shift)
    {
        m_max_intensity = 1.0;
    }

    ~IntensityScaleAndShiftNormalizer() final {}

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    void setMaximumIntensity(double) final {}

    IntensityScaleAndShiftNormalizer* clone() const final
    {
        return new IntensityScaleAndShiftNormalizer(m_scale, m_shift);
    }
};

#endif // BORNAGAIN_CORE_INTENSITY_IINTENSITYNORMALIZER_H
