// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ItemLink.cpp
//! @brief     Implements class ItemLink
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ItemLink.h"
#include "AngleProperty.h"


ItemLink::ItemLink(const QString name, ParameterizedItem *item)
    : m_name(name)
    , m_item(item)
    , m_value(0)
{

}

void ItemLink::setItem(QString name, ParameterizedItem *item)
{
    m_name = name;
    m_item = item;
}

double ItemLink::getValue() const
{
    return m_value;
}

void ItemLink::setValue(double value)
{
    m_value = value;
}

QVariant ItemLink::getVariant()
{
    QVariant variant = m_item->getRegisteredProperty(m_name);
    if(variant.typeName() == QString("double")) {
        variant.setValue(m_value);
        return variant;
    }
    else if(variant.typeName() == QString("AngleProperty")) {
        AngleProperty angle_property = variant.value<AngleProperty>();
        angle_property.setValue(m_value);
        return angle_property.getVariant();
    }

    return QVariant();
}

void ItemLink::updateItem()
{
    getItem()->setRegisteredProperty(getPropertyName(), getVariant());
}

