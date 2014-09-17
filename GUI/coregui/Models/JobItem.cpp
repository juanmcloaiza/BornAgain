#include "JobItem.h"
#include "JobQueueModel.h"
#include "JobRunner.h"
#include "OutputDataItem.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "GUIHelpers.h"
#include <QXmlStreamWriter>
#include <QDebug>
#include <QTimer>
#include <QThread>


QStringList JobItem::m_status_list = QStringList()
        << QString("Idle")
        << QString("Running")
        << QString("Completed")
        << QString("Canceled")
        << QString("Failed");

QStringList JobItem::m_run_policies = QStringList()
        << QString("Immediately")
        << QString("In background")
        << QString("Submit only");


JobItem::JobItem(const QString &name)
    : m_name(name)
    , m_status(Idle)
    , m_progress(0)
    , m_run_policy(SubmitOnly)
    , m_sampleModel(0)
    , m_instrumentModel(0)
{
    init();
}

JobItem::JobItem(SampleModel *sampleModel, InstrumentModel *instrumentModel, const QString &run_policy)
    : m_status(Idle)
    , m_progress(0)
    , m_run_policy(SubmitOnly)
    , m_sampleModel(sampleModel)
    , m_instrumentModel(instrumentModel)
{
    init();
    setRunPolicy(run_policy);
}


JobItem::~JobItem()
{
    clear();
}


void JobItem::clear()
{
    qDeleteAll(m_data_items);
    m_data_items.clear();
    delete m_sampleModel;
    delete m_instrumentModel;
}


void JobItem::init()
{
    OutputDataItem *dataItem = new OutputDataItem();
    m_data_items.append(dataItem);
    connect(dataItem, SIGNAL(modified()), this, SLOT(onDataItemModified()));
}


void JobItem::setName(QString name)
{
    m_name = name;
    // setting names for OutputDataItem's
    int n_data(0);
    foreach(OutputDataItem *dataItem, m_data_items) {
        QString dataFileName = QString("data_%1_%2.int").arg(m_name, QString::number(n_data));
        dataItem->setName(dataFileName);
        ++n_data;
    }

    emit modified(this);
}


QString JobItem::getStatusString() const
{
    return m_status_list.at(int(m_status));
}


OutputDataItem *JobItem::getOutputDataItem(int n_item)
{
    if(m_data_items.empty() || n_item < 0 || n_item >= m_data_items.size())
        return 0;
    return m_data_items.at(n_item);
}


// FIXME Make it nicer
void JobItem::setRunPolicy(const QString &run_policy)
{
    if(run_policy == QString("Immediately")) {
        m_run_policy = RunImmediately;
    } else if(run_policy == QString("In background")) {
        m_run_policy = RunInBackground;
    } else {
        m_run_policy = SubmitOnly;
    }
//    if(run_policy )
//    int index = m_run_policies.indexOf(run_policy);
//    if(index != -1) {
//        m_run_policy = (RunPolicy)index;
//    } else {
//        m_run_policy = SubmitOnly;
//    }
}


void JobItem::writeTo(QXmlStreamWriter *writer)
{
    Q_ASSERT(writer);
    writer->writeStartElement(JobQueueXML::JobTag);
    writer->writeAttribute(JobQueueXML::JobNameAttribute, getName());
    writer->writeAttribute(JobQueueXML::JobStatusAttribute, QString::number((int)getStatus()));
    writer->writeAttribute(JobQueueXML::JobBeginTimeAttribute, getBeginTime());
    writer->writeAttribute(JobQueueXML::JobEndTimeAttribute, getEndTime());
    writer->writeAttribute(JobQueueXML::JobCommentsAttribute, getComments());
    foreach(OutputDataItem *item, m_data_items) {
        item->writeTo(writer);
    }
    writer->writeEndElement(); // JobTag
}


void JobItem::readFrom(QXmlStreamReader *reader)
{
    Q_ASSERT(reader);
    clear();

    qDebug() << "JobQueueItem::readFrom() -> " << reader->name();
    if(reader->name() != JobQueueXML::JobTag) {
        throw GUIHelpers::Error("JobQueueItem::readFrom() -> Format error in p1");
    }

    setName(reader->attributes()
            .value(JobQueueXML::JobNameAttribute).toString());

    setBeginTime(reader->attributes()
            .value(JobQueueXML::JobBeginTimeAttribute).toString());

    setEndTime(reader->attributes()
            .value(JobQueueXML::JobEndTimeAttribute).toString());

    setComments(reader->attributes()
            .value(JobQueueXML::JobCommentsAttribute).toString());

    JobStatus status = (JobStatus) (reader->attributes()
            .value(JobQueueXML::JobStatusAttribute).toInt());
    setStatus(status);


    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {

            if (reader->name() == JobQueueXML::OutputDataTag) {
                qDebug() << "JobItem::readFrom() -> output data";
                OutputDataItem *item = new OutputDataItem();
                item->readFrom(reader);
                m_data_items.append(item);
            }
        } else if (reader->isEndElement()) {
            if (reader->name() == JobQueueXML::JobTag) {
                break; // end of xml of current Job
            }
        }
    }

}


