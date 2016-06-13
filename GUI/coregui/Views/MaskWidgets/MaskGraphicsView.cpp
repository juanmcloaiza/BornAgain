// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskGraphicsView.cpp
//! @brief     Implements class MaskGraphicsView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaskGraphicsView.h"
#include "MaskGraphicsProxy.h"
#include "MaskGraphicsScene.h"
#include <QWheelEvent>
#include <QGraphicsScene>
#include <QScrollBar>
#include <QTransform>
#include <QDebug>

namespace {
const double min_zoom_value = 1.0;
const double max_zoom_value = 5.0;
const double zoom_step = 0.05;
}

MaskGraphicsView::MaskGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
    , m_current_zoom_value(1.0)
{
    setObjectName(QStringLiteral("MaskGraphicsView"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setRenderHints(QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing);
    setMouseTracking(true);
}

//! Reset given view to original zoom state. Also asks graphics scene to do the same with color map.
void MaskGraphicsView::onResetViewRequest()
{
    qDebug() << "MaskGraphicsView::onResetViewRequest()";
    setZoomValue(1.0);
    MaskGraphicsScene *maskScene = dynamic_cast<MaskGraphicsScene *>(scene());
    maskScene->onResetViewRequest();
}

void MaskGraphicsView::wheelEvent(QWheelEvent *event)
{
    // hold control button
    if(isControlButtonIsPressed(event)) {
        centerOn(mapToScene(event->pos()));

        if(event->delta() > 0) {
            // Zoom in
            increazeZoomValue();

        } else {
            // Zooming out
            if(horizontalScrollBar()->isVisible() || verticalScrollBar()->isVisible())
                decreazeZoomValue();
        }
    } else {
        QGraphicsView::wheelEvent(event);
    }
}

//! On resize event changes scene size and MaskGraphicsProxy so they would get the size of viewport
void MaskGraphicsView::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    foreach (QGraphicsItem *graphicsItem, scene()->items()) {
        if(MaskGraphicsProxy *proxy = dynamic_cast<MaskGraphicsProxy *>(graphicsItem)) {
            proxy->resize(event->size());
            scene()->setSceneRect(0,0,event->size().width(),event->size().height());
            proxy->setPos(0,0);
            qDebug() << "!!! Resizing" << this->size() << event->size();
        }
    }
}

void MaskGraphicsView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        break;
    case Qt::Key_Space:
        if(!event->isAutoRepeat()) {
            emit changeActivityRequest(MaskEditorFlags::PAN_ZOOM_MODE);
        }
        break;
    case Qt::Key_Escape:
        cancelCurrentDrawing();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void MaskGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:
        if(!event->isAutoRepeat()) {
            emit changeActivityRequest(MaskEditorFlags::SELECTION_MODE);
        }
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}


bool MaskGraphicsView::isControlButtonIsPressed(QWheelEvent *event)
{
    if(event->modifiers().testFlag(Qt::ControlModifier)){
        return true;
    }
    return false;
}

void MaskGraphicsView::cancelCurrentDrawing()
{
    MaskGraphicsScene *maskScene = dynamic_cast<MaskGraphicsScene *>(scene());
    maskScene->cancelCurrentDrawing();
}

void MaskGraphicsView::setZoomValue(double zoom_value)
{
    if(zoom_value == m_current_zoom_value) return;
    QMatrix oldMatrix = matrix();
    resetMatrix();
    translate(oldMatrix.dx(), oldMatrix.dy());
    scale(zoom_value, zoom_value);
    m_current_zoom_value = zoom_value;
}

void MaskGraphicsView::decreazeZoomValue()
{
    double zoom_value = m_current_zoom_value - zoom_step;
    if(zoom_value < min_zoom_value) zoom_value = min_zoom_value;
    setZoomValue(zoom_value);
}

void MaskGraphicsView::increazeZoomValue()
{
    double zoom_value = m_current_zoom_value + zoom_step;
    if(zoom_value > max_zoom_value) zoom_value = max_zoom_value;
    setZoomValue(zoom_value);
}


