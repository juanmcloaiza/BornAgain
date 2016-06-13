// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/TestView.cpp
//! @brief     Implements class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //
#include "TestView.h"
#include "MaskEditor.h"
#include "ObsoleteRunFitWidget.h"
#include "ObsoleteFitView.h"
#include "mainwindow.h"
#include "ObsoleteFitParameterWidget.h"
#include "JobModel.h"
#include "MaterialEditor.h"
#include <QMimeData>
#include <QVBoxLayout>
#include <AccordionWidget.h>
#include <QLineEdit>
#include <QCheckBox>
#include <QTabWidget>

#include "SessionModel.h"
#include <QTreeView>
#include <SampleModel.h>
#include <InstrumentModel.h>
#include <JobModel.h>
#include <MaterialModel.h>
#include <QPersistentModelIndex>
#include "ModelMapper.h"
#include "DetectorItems.h"
#include "SessionModelDelegate.h"

TestView::TestView(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_mainWindow(mainWindow)
{
//    test_MaskEditor();
//    test_AccordionWidget();
//    test_RunFitWidget();
    test_sessionModel();
//    test_MaterialEditor();
}

void TestView::test_sessionModel()
{
    QVBoxLayout *layout = new QVBoxLayout;
    QTabWidget *tabs = new QTabWidget;

//    addModelToTabs(tabs, m_mainWindow->instrumentModel());
//    addModelToTabs(tabs, m_mainWindow->sampleModel());
//    addModelToTabs(tabs, m_mainWindow->materialModel());
    addModelToTabs(tabs, m_mainWindow->jobModel());

    TestProxyModel *testModel = new TestProxyModel(this);
    testModel->setSourceModel(m_mainWindow->sampleModel());
    addModelToTabs(tabs, testModel);

    // TODO: why is instrument empty here?
    // do some testing here
//    m_mainWindow->getInstrumentModel()->rootItem()->getChildOfType(Constants::InstrumentType)->mapper()
//            ->setOnChildPropertyChange(
//                [](SessionItem* item, const QString &name) {
//        qDebug() << "Property Changed from " << item->itemName() << " (" << item->modelType() << " )"
//                 << "with name " << name;
//    });

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(tabs);
    setLayout(layout);
}

void TestView::test_MaterialEditor()
{
    MaterialEditor *materialEditor = new MaterialEditor(m_mainWindow->materialModel());
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(materialEditor);
    setLayout(layout);
}

void TestView::addModelToTabs(QTabWidget *tabs, QAbstractItemModel *model)
{
    QTreeView *view = new QTreeView;
    SessionModelDelegate *delegate = new SessionModelDelegate(this);

    view->setModel(model);
    view->setItemDelegate(delegate);

    view->expandAll();
    view->resizeColumnToContents(0);
    view->resizeColumnToContents(1);
    if (SessionModel *sm = dynamic_cast<SessionModel*>(model))
        tabs->addTab(view, sm->getModelTag());
    else
        tabs->addTab(view, "Some Model");
}

void TestView::test_MaskEditor()
{
    MaskEditor *maskEditor = new MaskEditor();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(maskEditor);
    setLayout(layout);

    maskEditor->init_test_model();
}

void TestView::test_AccordionWidget()
{
    AccordionWidget *myAccordion = new AccordionWidget();
    myAccordion->setMultiActive(true);
    // add the Accordion to your layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(myAccordion);
    setLayout(layout);

    // add a content pane with a header
    int firstPaneIndex = myAccordion->addContentPane("My first content pane");
    // make sure our content pane was added
    if (firstPaneIndex != -1) {
        // get a QFrame* from the Content Pane. This is where we place our content
        QFrame *contentFrame = myAccordion->getContentPane(firstPaneIndex)->getContentFrame();
        // give the QFrame a QLayout
        contentFrame->setLayout(new QVBoxLayout());
        // add a simpel QLabel to the frame
        contentFrame->layout()->addWidget(new QLabel("Hello Cute World!!!"));
    }

    // add a content pane with a header
    int secondPaneIndex = myAccordion->addContentPane("Basic settings");
    // make sure our content pane was added
    if (secondPaneIndex != -1) {
        // get a QFrame* from the Content Pane. This is where we place our content
        QFrame *contentFrame = myAccordion->getContentPane(secondPaneIndex)->getContentFrame();
        // give the QFrame a QLayout
        contentFrame->setLayout(new QVBoxLayout());
        // add a simpel QLabel to the frame
        QLineEdit *led = new QLineEdit();
        QLineEdit *led2 = new QLineEdit();
        contentFrame->layout()->addWidget(new QLabel("Name:"));
        contentFrame->layout()->addWidget(led);
        contentFrame->layout()->addWidget(new QLabel("Living place:"));
        contentFrame->layout()->addWidget(led2);
    }

    // add a content pane with a header
    int third = myAccordion->addContentPane("Advanced");
    // make sure our content pane was added
    if (third != -1) {
        // get a QFrame* from the Content Pane. This is where we place our content
        myAccordion->getContentPane(third)->setMaximumHeight(500);
        QFrame *contentFrame = myAccordion->getContentPane(third)->getContentFrame();
        contentFrame->setMaximumHeight(500);
        // give the QFrame a QLayout
        contentFrame->setLayout(new QVBoxLayout());
        // add a simpel QLabel to the frame
        QCheckBox *cb = new QCheckBox();
        cb->setText("Option 1");
        QCheckBox *cb2 = new QCheckBox();
        cb2->setText("Option 2");
        QCheckBox *cb3 = new QCheckBox();
        cb3->setText("Option 3");
        QCheckBox *cb4 = new QCheckBox();
        cb4->setText("Option 4");
        QCheckBox *cb5 = new QCheckBox();
        cb5->setText("Option 5");
        QCheckBox *cb6 = new QCheckBox();
        cb6->setText("Option 6");
        QCheckBox *cb7 = new QCheckBox();
        cb7->setText("Option 7");
        contentFrame->layout()->addWidget(cb);
        contentFrame->layout()->addWidget(cb2);
        contentFrame->layout()->addWidget(cb3);
        contentFrame->layout()->addWidget(cb4);
        contentFrame->layout()->addWidget(cb5);
        contentFrame->layout()->addWidget(cb6);
        contentFrame->layout()->addWidget(cb7);

    }
}

void TestView::test_RunFitWidget()
{
    // FIXME_DAVID Use consistent variable names: not 'maskEditor', but runFitWidget

    //RunFitWidget *maskEditor = new RunFitWidget();
    //FitView *fw = new FitView(m_mainWindow->getSampleModel(), m_mainWindow->getInstrumentModel());

    //FitParameterWidget *fitting = new FitParameterWidget(m_mainWindow);
    QVBoxLayout *layout = new QVBoxLayout;
    QTabWidget *tabs = new QTabWidget;
    //tabs->addTab(maskEditor, "Run Fit");
    //tabs->addTab(fw, "FitView by Ivonna");
    //tabs->addTab(fitting, "Test TreeView");
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(tabs);
    setLayout(layout);

}

TestProxyModel::TestProxyModel(QObject *parent)
    : QIdentityProxyModel(parent)
{
}

void TestProxyModel::setSourceModel(QAbstractItemModel *source)
{
    QIdentityProxyModel::setSourceModel(source);
    m_source = dynamic_cast<SessionModel*>(source);
    connect(m_source, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SIGNAL(layoutChanged()));
}

QModelIndex TestProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    const QModelIndex sourceParent = mapToSource(parent);
    SessionItem *parentt = m_source->itemForIndex(sourceParent);
    if (parentt->modelType() == Constants::GroupItemType) {
        SessionItem *cur = parentt->parent()->getGroupItem(parentt->itemName());
        const QModelIndex sourceIndex = m_source->index(row, column, cur->index());
        return mapFromSource(sourceIndex);
    }
    const QModelIndex sourceIndex = m_source->index(row, column, sourceParent);
    return mapFromSource(sourceIndex);
}

QModelIndex TestProxyModel::parent(const QModelIndex &child) const
{
    const QModelIndex sourceIndex = mapToSource(child);
    SessionItem *head = m_source->itemForIndex(sourceIndex.parent());
    if (head && head->parent() && head->parent()->modelType() == Constants::GroupItemType) {
        // skip immediate layer
        return mapFromSource(head->parent()->index());
    }
    const QModelIndex sourceParent = sourceIndex.parent();
    return mapFromSource(sourceParent);
}

int TestProxyModel::rowCount(const QModelIndex &parent) const
{
    QModelIndex sourceParent = mapToSource(parent);
    SessionItem *item = m_source->itemForIndex(sourceParent);
    if (item && item->modelType() == Constants::GroupItemType) {
        SessionItem *cur = item->parent()->getGroupItem(item->itemName());
        if (cur)
            return m_source->rowCount(cur->index());
        else
            qDebug() << "proxy::rowCount: null pointer";
    }
    return m_source->rowCount(sourceParent);
}
