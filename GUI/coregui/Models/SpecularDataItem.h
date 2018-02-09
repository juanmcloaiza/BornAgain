// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SpecularDataItem.h
//! @brief     Defines class SpecularDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARDATAITEM_H
#define SPECULARDATAITEM_H

#include "SessionItem.h"
#include "OutputData.h"
#include <QDateTime>

class AmplitudeAxisItem;
class BasicAxisItem;
class MaskContainerItem;
class ProjectionContainerItem;

class BA_CORE_API_ SpecularDataItem : public SessionItem
{
public:
    static const QString P_TITLE;
    static const QString P_AXES_UNITS;
    static const QString P_XAXIS;
    static const QString P_YAXIS;
    static const QString P_FILE_NAME;

    SpecularDataItem();

    OutputData<double>* getOutputData() { return m_data.get(); }
    const OutputData<double>* getOutputData() const { return m_data.get(); }
    void setOutputData(OutputData<double>* data);
    void setRawDataVector(const OutputData<double>* data);

    //! Number of bins in data
    int getNbins() const;

    //! returns lower and upper zoom ranges of x-axis
    double getLowerX() const;
    double getUpperX() const;

    //! returns min and max range of x-axis as given by IntensityData
    double getXmin() const;
    double getXmax() const;

    //! returns lower and upper zoom ranges of y-axis
    double getLowerY() const;
    double getUpperY() const;

    //! returns min and max range of y-axis as given by IntensityData
    double getYmin() const;
    double getYmax() const;

    bool isLog() const;
    QString getXaxisTitle() const;
    QString getYaxisTitle() const;

    QString selectedAxesUnits() const;

    QString fileName(const QString& projectDir = QString()) const;

    void updateDataRange();
    void computeDataRange();
    QPair<double, double> dataRange() const;

    const BasicAxisItem* xAxisItem() const;
    BasicAxisItem* xAxisItem();
    const AmplitudeAxisItem* yAxisItem() const;

    void resetView();

    QDateTime lastModified() const;
    void setLastModified(const QDateTime& dtime);

public slots:
    void setLowerX(double xmin);
    void setUpperX(double xmax);
    void setLowerY(double ymin);
    void setUpperY(double ymax);
    void setLog(bool log_flag);
    void setXaxisTitle(QString xtitle);
    void setYaxisTitle(QString ytitle);
    void setAxesRangeToData();

private:
    void updateAxesZoomLevel();
    void updateAxesLabels();

    std::unique_ptr<OutputData<double>> m_data; //!< simulation results
    QDateTime m_last_modified;
};

#endif // SPECULARDATAITEM_H