// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorTools.cpp
//! @brief     Implements global functions that facilitate IFormFactor handling.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTools.h"
#include "FormFactorDWBA.h"
#include "FormFactorDWBAPol.h"

IFormFactor* FormFactorTools::createDWBAScalarFormFactor(
        IFormFactor* p_form_factor)
{
    FormFactorDWBA *p_result =
        new FormFactorDWBA(p_form_factor);
    return p_result;
}

IFormFactor* FormFactorTools::createDWBAMatrixFormFactor(
        IFormFactor* p_form_factor)
{
    FormFactorDWBAPol *p_result = new FormFactorDWBAPol(p_form_factor);
    return p_result;
}
