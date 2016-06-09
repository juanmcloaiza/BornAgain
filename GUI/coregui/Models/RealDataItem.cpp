// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/RealDataItem.h
//! @brief     Implements class RealDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealDataItem.h"
#include "IntensityDataItem.h"
#include "GUIHelpers.h"

const QString RealDataItem::T_INTENSITY_DATA = "Intensity data";

RealDataItem::RealDataItem()
    : SessionItem(Constants::RealDataType)
{
    setItemName(QStringLiteral("undefined"));
    registerTag(T_INTENSITY_DATA, 1, 1, QStringList() << Constants::IntensityDataType);
    setDefaultTag(T_INTENSITY_DATA);

    mapper()->setOnPropertyChange(
        [this](const QString &name){
        if(name == P_NAME && isTag(T_INTENSITY_DATA))
            updateIntensityDataFileName();
        }
    );

    mapper()->setOnChildrenChange(
        [this](SessionItem *item){
        if(item && item->modelType() == Constants::IntensityDataType)
            updateIntensityDataFileName();
        }
    );

}

IntensityDataItem *RealDataItem::intensityDataItem()
{
    return const_cast<IntensityDataItem *>(static_cast<const RealDataItem*>(this)->intensityDataItem());
}

const IntensityDataItem *RealDataItem::intensityDataItem() const
{
    const IntensityDataItem *result = dynamic_cast<const IntensityDataItem *>(getItem(T_INTENSITY_DATA));
    return result;
}

//! Updates the name of file to store intensity data.

void RealDataItem::updateIntensityDataFileName()
{
    if(IntensityDataItem *item = intensityDataItem()) {
        QString newFileName = GUIHelpers::intensityDataFileName(this);
        item->setItemValue(IntensityDataItem::P_FILE_NAME, newFileName);
    }
}