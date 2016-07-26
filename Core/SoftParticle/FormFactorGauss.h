// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorGauss.h
//! @brief     Declares class FormFactorGauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORGAUSS_H
#define FORMFACTORGAUSS_H

#include "IFormFactorBorn.h" // inheriting from

//! @class FormFactorGauss
//! @ingroup formfactors
//! @brief The formfactor of a gaussian.

class BA_CORE_API_ FormFactorGauss : public IFormFactorBorn
{
public:
    FormFactorGauss(double volume);
    FormFactorGauss(double width, double height);
    virtual ~FormFactorGauss() {}
    virtual FormFactorGauss *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    virtual complex_t evaluate_for_q(const cvector_t q) const;

    //! Returns height
    double getHeight() const;

    //! Returns width
    virtual double getRadius() const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_width;
    double m_height;
    double m_max_ql;
    void initialize();
};

inline double FormFactorGauss::getHeight() const
{
    return m_height;
}

inline double FormFactorGauss::getRadius() const
{
    return m_width;
}

#endif // FORMFACTORGAUSS_H

