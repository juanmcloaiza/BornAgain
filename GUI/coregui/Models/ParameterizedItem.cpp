// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      ParameterizedItem.h
//! @brief     Defines class ParameterizedItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParameterizedItem.h"
#include "Exceptions.h"



ParameterizedItem::ParameterizedItem(const QString &name)
    : QStandardItem(name)
{
}

ParameterizedItem::~ParameterizedItem()
{
}

double ParameterizedItem::getParameterValue(const QString &name) const
{
    if (!m_parameters.contains(name)) {
        throw Exceptions::RuntimeErrorException("ParameterizedItem::getParameterValue: "
                                                "parameter does not exist");
    }
    return m_parameters[name];
}

void ParameterizedItem::setParameter(const QString &name, double value)
{
    if (!m_parameters.contains(name)) {
        throw Exceptions::RuntimeErrorException("ParameterizedItem::getParameterValue: "
                                                "parameter does not exist");
    }
    m_parameters[name] = value;
}

bool ParameterizedItem::acceptsAsChild(const QString &child_name) const
{
    return m_valid_children.contains(child_name);
}

