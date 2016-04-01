// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/ComponentEditor.h
//! @brief     Defines class ComponentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTEDITOR_H
#define COMPONENTEDITOR_H

#include "WinDllMacros.h"
#include "ComponentEditorFlags.h"
#include <QWidget>
#include <memory>

class ComponentEditorPrivate;
class SessionItem;
class SessionModel;
class QtVariantProperty;
class QtProperty;

class BA_CORE_API_ ComponentEditor : public QWidget
{
    Q_OBJECT
public:
    ComponentEditor(ComponentEditorFlags::PresentationType flags = ComponentEditorFlags::BROWSER_TABLE, QWidget *parent = 0);

    virtual ~ComponentEditor();

    void setItem(SessionItem *item, const QString &group_name=QString());

    void updateEditor(SessionItem *item, QtVariantProperty *parentProperty = 0);

    void clearEditor();

public slots:
    virtual void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
    virtual void onRowsInserted(const QModelIndex &parent, int first, int last);

private slots:
    void onQtPropertyChanged(QtProperty *, const QVariant &value);

protected:
    QList<SessionItem *> componentItems(SessionItem *item) const;
    void cleanChildren(SessionItem *item);

    void disconnectModel(SessionModel *model);
    void connectModel(SessionModel *model);
    void disconnectManager();
    void connectManager();

    std::unique_ptr<ComponentEditorPrivate> m_d;
};


#endif