// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorPrism3.cpp
//! @brief     Implements class FormFactorPrism3.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorPrism3.h"
#include "AttLimits.h"
#include "BornAgainNamespace.h"
#include <iostream>

//! @brief Prism3 constructor
//! @param base_edge of hexagonal base
//! @param height of Prism3
FormFactorPrism3::FormFactorPrism3(const double base_edge, const double height)
    : FormFactorPolygonalPrism( height )
    , m_base_edge( base_edge )
{
    setName(BornAgain::FFPrism3Type);
    registerParameter(BornAgain::BaseEdge, &m_base_edge, AttLimits::n_positive());
    registerParameter(BornAgain::Height, &m_height, AttLimits::n_positive());
    onChange();
}

void FormFactorPrism3::onChange()
{
    double a = m_base_edge;
    double as = a/2;
    double ac = a/sqrt(3)/2;
    double ah = a/sqrt(3);
    std::vector<kvector_t> V {
        { -ac,  as, 0. },
        { -ac, -as, 0. },
        {  ah,  0., 0. } };
    setPrism( false, V );
}

FormFactorPrism3* FormFactorPrism3::clone() const
{
    return new FormFactorPrism3(m_base_edge, m_height);
}

void FormFactorPrism3::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}