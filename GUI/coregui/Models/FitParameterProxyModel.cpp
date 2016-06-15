// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FitParameterAbsModel.cpp
//! @brief     Implements class FitParameterAbsModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitParameterProxyModel.h"
#include "SessionItem.h"
#include "FitParameterItems.h"
#include "SessionModel.h"
#include "JobModel.h"
#include "FitParameterHelper.h"
#include "ParameterTreeItems.h"
#include "GUIHelpers.h"
#include "ModelPath.h"
#include <QColor>
#include <QMimeData>
#include <QDebug>


FitParameterProxyModel::FitParameterProxyModel(FitParameterContainerItem *fitParContainer, QObject *parent)
    : QAbstractItemModel(parent)
    , m_root_item(fitParContainer)
{
    addColumn(PAR_NAME, QStringLiteral("Name"), QStringLiteral("Name of fit parameter"));
    addColumn(PAR_TYPE, FitParameterItem::P_TYPE, QStringLiteral("Fit parameter limits type"));
    addColumn(PAR_VALUE, FitParameterItem::P_START_VALUE, QStringLiteral("Starting value of fit parameter"));
    addColumn(PAR_MIN, FitParameterItem::P_MIN, QStringLiteral("Lower bound on fit parameter value"));
    addColumn(PAR_MAX, FitParameterItem::P_MAX, QStringLiteral("Upper bound on fit parameter value"));

    connectModel(fitParContainer->model());

    m_root_item->mapper()->setOnItemDestroy(
                [this](SessionItem *parentItem) {
        if(parentItem != m_root_item) {
            throw GUIHelpers::Error("FitParameterProxyModel::FitParameterProxyModel() -> Error. "
                                    "Wrong item reported.");
        }
        m_root_item = 0;
    });
}

Qt::ItemFlags FitParameterProxyModel::flags(const QModelIndex &index) const
{
    if(!m_root_item) return Qt::NoItemFlags;

    Qt::ItemFlags returnVal = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if(SessionItem *item = itemForIndex(index)) {
        if(item->isEditable() && index.column() != 0) returnVal |= Qt::ItemIsEditable;
        if(item->parent()->modelType() == Constants::FitParameterLinkType && index.column() == 0) {
            returnVal |= Qt::ItemIsDragEnabled;
        }
        if(item->modelType() == Constants::FitParameterType || item->modelType() == Constants::FitParameterContainerType) {
            returnVal |= Qt::ItemIsDropEnabled;
        }

    }

    return returnVal;
}

QModelIndex FitParameterProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!m_root_item || row < 0 || column < 0 || column >= columnCount(QModelIndex())
        || (parent.isValid() && parent.column() != 0))
        return QModelIndex();

    SessionItem *parent_item = itemForIndex(parent);
//    if(!isValidSourceItem(parent_item)) return QModelIndex();
    Q_ASSERT(parent_item);

    if(parent_item->modelType() == Constants::FitParameterContainerType) {
        if (SessionItem *fitParItem = parent_item->childAt(row)) {
            SessionItem *itemToPack = fitParItem;
            if(column != 0) {
                itemToPack = fitParItem->getItem(m_columnNames.value(column));
            }
            return createIndex(row, column, itemToPack);
        }
    }

    else if(parent_item->modelType() == Constants::FitParameterType && column == 0) {
        QVector<SessionItem *> links = parent_item->getItems(FitParameterItem::T_LINK);
        if(row < links.size()) {
            if(SessionItem *linkItem = links.at(row)) {
                return createIndex(row, column, linkItem->getItem(FitParameterLinkItem::P_LINK));
            }
        }
    }

    return QModelIndex();
}

QModelIndex FitParameterProxyModel::parent(const QModelIndex &child) const
{
    if(!m_root_item)
        return QModelIndex();

    if (!child.isValid())
        return QModelIndex();

    if (SessionItem *child_item = itemForIndex(child)) {
        if (SessionItem *parent_item = child_item->parent()) {

            if(!isValidSourceItem(parent_item)) return QModelIndex();

            if(parent_item->modelType()==Constants::FitParameterLinkType) {
                SessionItem *fitPar = parent_item->parent();

                if(!isValidSourceItem(fitPar)) return QModelIndex();

                return createIndex(fitPar->parentRow(), 0, fitPar);
            }
        }

    }

    return QModelIndex();
}

int FitParameterProxyModel::rowCount(const QModelIndex &parent) const
{
    if(!m_root_item) return 0;

    if (parent.isValid() && parent.column() != 0)
        return 0;

    SessionItem *parent_item = itemForIndex(parent);
    if(parent_item!=m_root_item && !isValidSourceItem(parent_item)) return 0;

    if(parent_item->modelType() == Constants::FitParameterContainerType) {
        return parent_item->rowCount();
    }

    else if(parent_item->modelType() == Constants::FitParameterType) {
        return parent_item->getItems(FitParameterItem::T_LINK).size();
    }

    return 0;
}

int FitParameterProxyModel::columnCount(const QModelIndex &parent) const
{
    if(!m_root_item) return 0;

    if (parent.isValid() && parent.column() != 0)
        return 0;

    if(!parent.isValid())
        return MAX_COLUMNS;

    if(parent.isValid()) {
        if(SessionItem *parentItem = itemForIndex(parent)) {
            if(parentItem->modelType() == Constants::FitParameterType) {
                return (parentItem->getItems(FitParameterItem::T_LINK).size() ? 1 : 0);
            }
        }

    }

    return 0;
}

QVariant FitParameterProxyModel::data(const QModelIndex &index, int role) const
{
    if(!m_root_item) return QVariant();

    if ( !index.isValid() || index.column() < 0 || index.column() >= MAX_COLUMNS)
        return QVariant();

    if (SessionItem *item = itemForIndex(index)) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            if(item->modelType() == Constants::FitParameterType) {
                return item->displayName();
            } else {
                return item->value();
            }
        }
        if(role == Qt::TextColorRole && !item->isEditable()) {
            return QVariant(QColor(Qt::gray));
        }
    }

    return QVariant();
}

bool FitParameterProxyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!m_root_item) return false;

    if (!index.isValid())
        return false;
    if (SessionItem *item = itemForIndex(index)) {
        if (role == Qt::EditRole) {
            item->setValue(value);
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

QStringList FitParameterProxyModel::mimeTypes() const
{
    QStringList types;
    types << SessionXML::LinkMimeType;
    return types;
}

QMimeData *FitParameterProxyModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QModelIndex index = indexes.first();
    if (index.isValid()) {
        if(SessionItem *item = itemForIndex(index)) {
            QString path = item->value().toString();
            mimeData->setData(SessionXML::LinkMimeType, path.toLatin1());
        }
    }
    return mimeData;
}

bool FitParameterProxyModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(data);
    Q_UNUSED(action);
    Q_UNUSED(row);
    bool drop_is_possible(false);
    if(parent.isValid()) drop_is_possible = true;
    if(!parent.isValid() && row==-1 && column == -1) drop_is_possible = true;
    return drop_is_possible;
}

bool FitParameterProxyModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                                        int column, const QModelIndex &parent)
{
    Q_UNUSED(action);
    Q_UNUSED(row);
    Q_UNUSED(column);

    if (parent.isValid()) {
        if (SessionItem *fitParItem = itemForIndex(parent)) {
            Q_ASSERT(fitParItem->modelType() == Constants::FitParameterType);
            ParameterItem *parItem = FitParameterHelper::getParameterItem(
                m_root_item, QString::fromLatin1(data->data(SessionXML::LinkMimeType)));
            Q_ASSERT(parItem);
            FitParameterHelper::addToFitParameter(m_root_item, parItem, fitParItem->displayName());
        }

    } else {
        ParameterItem *parItem = FitParameterHelper::getParameterItem(
            m_root_item, QString::fromLatin1(data->data(SessionXML::LinkMimeType)));
        Q_ASSERT(parItem);
        FitParameterHelper::createFitParameter(m_root_item, parItem);
    }

    return true;
}

QVariant FitParameterProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_columnNames.value(section);
    }
    else if(role == Qt::ToolTipRole) {
        return m_columnToolTips.value(section);
    }
    return QVariant();
}

void FitParameterProxyModel::onSourceDataChanged(const QModelIndex &topLeft,
                                               const QModelIndex &bottomRight,
                                               const QVector<int> &roles)
{
    Q_UNUSED(bottomRight);

    JobModel *sourceModel = qobject_cast<JobModel *>(sender());
    Q_ASSERT(sourceModel);
    SessionItem *sourceItem = sourceModel->itemForIndex(topLeft);

    QModelIndex itemIndex = indexOfItem(sourceItem);

    if (itemIndex.isValid())
        emit dataChanged(itemIndex, itemIndex, roles);
}

void FitParameterProxyModel::onSourceRowsRemoved(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);
    beginResetModel();
    endResetModel();
}

void FitParameterProxyModel::onSourceAboutToBeReset()
{
    if(!m_root_item) return;
    beginResetModel();
    endResetModel();
}

void FitParameterProxyModel::connectModel(QAbstractItemModel *sourceModel, bool isConnect)
{
    Q_ASSERT(sourceModel);
    if(isConnect) {
        connect(sourceModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                this, SLOT(onSourceDataChanged(QModelIndex,QModelIndex,QVector<int>)));
        connect(sourceModel, SIGNAL(rowsRemoved(QModelIndex,int,int)),
                   this, SLOT(onSourceRowsRemoved(QModelIndex,int,int)));
        connect(sourceModel, SIGNAL(modelAboutToBeReset()), this, SLOT(onSourceAboutToBeReset()));

    }

    else {
        disconnect(sourceModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                this, SLOT(onSourceDataChanged(QModelIndex,QModelIndex,QVector<int>)));
        disconnect(sourceModel, SIGNAL(rowsRemoved(QModelIndex,int,int)),
                   this, SLOT(onSourceRowsRemoved(QModelIndex,int,int)));
        disconnect(sourceModel, SIGNAL(modelAboutToBeReset()), this, SLOT(onSourceAboutToBeReset()));
    }
}

void FitParameterProxyModel::addColumn(FitParameterProxyModel::EColumn id, const QString &name,
                                     const QString &tooltip)
{
    m_columnNames[id] = name;
    m_columnToolTips[id] = tooltip;
}

QModelIndex FitParameterProxyModel::indexOfItem(SessionItem *item) const
{
    if(!m_root_item) return QModelIndex();

    if(SessionItem *parent_item = item->parent()) {
        if(parent_item->modelType() == Constants::FitParameterContainerType) {
            if(item->modelType() == Constants::FitParameterType) {
                return createIndex(item->parentRow(), 0, item);
            }
        }

        else if(parent_item->modelType() == Constants::FitParameterType) {

            QString tag = parent_item->tagFromItem(item);
            int col = m_columnNames.key(tag, -1);
            if(col > 0) {
                return createIndex(parent_item->parentRow(), col, item);
            }
        }

        else if(parent_item->modelType() == Constants::FitParameterLinkType) {
            QVector<SessionItem *> links = parent_item->parent()->getItems(FitParameterItem::T_LINK);
            return createIndex(links.indexOf(parent_item), 0, item);
        }

    }

    return QModelIndex();
}

SessionItem *FitParameterProxyModel::itemForIndex(const QModelIndex &index) const
{
    if(!m_root_item) return 0;

    if (index.isValid()) {
        SessionItem *item = static_cast<SessionItem *>(index.internalPointer());
        if(item) {
            if(!isValidSourceItem(item)) {
                return 0;
//                throw GUIHelpers::Error("FitParameterAbsModel::itemForIndex -> Error! Attempt to "
//                                    "use destroyed item.");
            }

            return item;
        }
    }
    return m_root_item;
}

SessionModel *FitParameterProxyModel::sourceModel() const
{
    Q_ASSERT(m_root_item);
    return m_root_item->model();
}

//! Returns true if given item still exists in source model
bool FitParameterProxyModel::isValidSourceItem(SessionItem *item) const
{
    if(item == m_root_item) return true;
    if(sourceModel() && ModelPath::isValidItem(sourceModel(), item, m_root_item->index()))
        return true;
    return false;
}
