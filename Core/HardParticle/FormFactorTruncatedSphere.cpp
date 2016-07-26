// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTruncatedSphere.cpp
//! @brief     Implements class FormFactorTruncatedSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTruncatedSphere.h"
#include "AttLimits.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "MathFunctions.h"
#include "Numeric.h"
#include "Units.h"

using namespace  BornAgain;

FormFactorTruncatedSphere::FormFactorTruncatedSphere(double radius, double height)
    : m_radius(radius)
    , m_height(height)
{
    setName(FFTruncatedSphereType);
    check_initialization();
    init_parameters();

    mP_integrator = make_integrator_complex(this, &FormFactorTruncatedSphere::Integrand);
}

FormFactorTruncatedSphere::~FormFactorTruncatedSphere() {}

bool FormFactorTruncatedSphere::check_initialization() const
{
    bool result(true);
    if(m_height > 2.*m_radius) {
        std::ostringstream ostr;
        ostr << "::FormFactorTruncatedSphere() -> Error in class initialization ";
        ostr << "with parameters 'radius':" << m_radius << " 'height':" << m_height << "\n\n";
        ostr << "Check for height <= 2.*radius failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

void FormFactorTruncatedSphere::init_parameters()
{
    registerParameter(Radius, &m_radius, AttLimits::n_positive());
    registerParameter(Height, &m_height, AttLimits::n_positive());
}

FormFactorTruncatedSphere *FormFactorTruncatedSphere::clone() const
{
    return new FormFactorTruncatedSphere(m_radius, m_height);
}

void FormFactorTruncatedSphere::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

//! Integrand for complex formfactor.
complex_t FormFactorTruncatedSphere::Integrand(double Z) const
{
    double Rz = std::sqrt(m_radius*m_radius-Z*Z );
    complex_t qx = m_q.x();
    complex_t qy = m_q.y();
    complex_t q_p = std::sqrt(qx*qx + qy*qy); // NOT the modulus!
    return Rz*Rz*MathFunctions::Bessel_J1c(q_p*Rz) * exp_I(m_q.z()*Z);
}

//! Complex formfactor.
complex_t FormFactorTruncatedSphere::evaluate_for_q(const cvector_t q) const
{
    m_q = q;
    if ( std::abs(q.mag()) < Numeric::double_epsilon) {
        double HdivR = m_height/m_radius;
        return Units::PI/3.*m_radius*m_radius*m_radius
                *(3.*HdivR -1. - (HdivR - 1.)*(HdivR - 1.)*(HdivR - 1.));
    }
    // else
    complex_t integral = mP_integrator->integrate(m_radius-m_height, m_radius);
    return Units::PI2 * integral * exp_I(q.z()*(m_height-m_radius));
}