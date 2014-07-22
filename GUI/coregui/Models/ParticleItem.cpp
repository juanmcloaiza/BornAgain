// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/ParticleItem.cpp
//! @brief     Implements class ParticleItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleItem.h"
#include "FormFactorItems.h"
#include "MaterialUtils.h"
#include <QDebug>

const QString ParticleItem::P_FORM_FACTOR = "Form Factor";
const QString ParticleItem::P_DEPTH = "Depth";
const QString ParticleItem::P_ABUNDANCE = "Abundance";
const QString ParticleItem::P_MATERIAL = "Material";



ParticleItem::ParticleItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::ParticleType, parent)
{
    setItemName(Constants::ParticleType);
    setItemPort(ParameterizedItem::PortInfo::Port0);
    //registerGroupProperty(P_FORM_FACTOR, Constants::CylinderType);
    registerFancyGroupProperty(P_FORM_FACTOR, Constants::FormFactorGroup);

    registerProperty(P_MATERIAL, MaterialUtils::getDefaultMaterialProperty().getVariant());

    registerProperty(P_DEPTH, 0.0);
    registerProperty(P_ABUNDANCE, 1.0);
}

