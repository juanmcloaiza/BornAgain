// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/ILayerView.h
//! @brief     Defines class ILayerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ILAYERVIEW_H
#define ILAYERVIEW_H

#include "ConnectableView.h"

class MultiLayerView;
class MultiLayerCandidate;

//! Base class for LayerView and MultiLayerView
//! Provides functionality for moving view on top of MultiLayer.
class BA_CORE_API_ ILayerView : public ConnectableView
{
    Q_OBJECT

public:
    ILayerView(QGraphicsItem *parent = 0);

    enum { TYPE = DesignerHelper::LAYER };

    int type() const { return TYPE; }

    void setParameterizedItem(ParameterizedItem *item);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void onPropertyChange(const QString &propertyName);

private:
    MultiLayerCandidate getMultiLayerCandidate();
    QPointF m_drag_start_position;
};


//! Class to hold MultiLayer candidate for dropping LayerView.
class MultiLayerCandidate
{
public:
    MultiLayerCandidate() : multilayer(0), row(-1), distance(0){}
    MultiLayerView *multilayer; //!< pointer to the candidate
    int row; //!< requested row number to drop in
    int distance; //!< distance from given ILayerView and drop area
    bool operator< (const MultiLayerCandidate& cmp) const;
    operator bool() const { return bool(multilayer); }
    //! returns line representing interface of multilayer in scene coordinates
    QLineF getInterfaceToScene();
};


#endif