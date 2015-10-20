// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IHistogram.h
//! @brief     Defines class IHistogram.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IHISTOGRAM_H
#define IHISTOGRAM_H

#include "OutputData.h"
#include "CumulativeValue.h"

#ifdef BORNAGAIN_PYTHON
#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif
#endif

class Histogram1D;
class Histogram2D;

//! @class IHistogram
//! @ingroup tools
//! @brief Base class for 1D and 2D histograms holding values of double type

class IHistogram
{
public:
    enum DataType {INTEGRAL, AVERAGE, ERROR, NENTRIES};

    IHistogram();
    virtual ~IHistogram(){}

    IHistogram(const IAxis &axis_x);
    IHistogram(const IAxis &axis_x, const IAxis &axis_y);

    //! Returns number of histogram dimensions.
    virtual size_t getRank() const;

    //! Returns total number of histogram bins. For 2D histograms the result will be the product
    //! of bin numbers along X and Y axes.
    size_t getTotalNumberOfBins() const;

    //! returns x-axis
    const IAxis *getXaxis() const;

    //! returns y-axis for 2D histograms
    const IAxis *getYaxis() const;

    //! Returns x-axis min (lower edge of first bin).
    double getXmin() const;

    //! Returns x-axis max (upper edge of last bin).
    double getXmax() const;

    //! Returns number of bins on x-axis
    size_t getNbinsX() const;

    //! Returns y-axis min (lower edge of first bin) for 2D histograms.
    double getYmin() const;

    //! Returns y-axis max (upper edge of last bin) for 2D histograms.
    double getYmax() const;

    //! Returns number of bins on y-axis
    size_t getNbinsY() const;

    //! Returns global bin index for given axes indices. For 1D histogram the global bin
    //! index coinside with x-axis index.
    //! @param binx x-axis bin index
    //! @param biny y-axis bin index (for 2D histograms)
    //! @return The global bin index
    size_t getGlobalBin(size_t binx, size_t biny = 0) const;

    //! Returns closest global bin index for given axes coordinates. For 1D
    //! @param x Value on x-axis
    //! @param y Value on y-axis (for 2D histograms)
    //! @return Closest global bin index
    size_t findGlobalBin(double x, double y) const;

    //! Returns x-axis bin index for given globalbin. For 1D histograms returned value conicide
    //! with globalbin value.
    int getXaxisIndex(size_t globalbin) const;

    //! Returns y-axis bin index for given globalbin (for 2D histograms).
    int getYaxisIndex(size_t globalbin) const;

    //! Returns the value on x-axis corresponding to the global bin index.
    //! @param globalbin The global bin index
    //! @return The center of corresponding bin of the axis
    double getXaxisValue(size_t globalbin);

    //! Returns the value on y-axis corresponding to the global bin index (for 2D histograms).
    //! @param globalbin The global bin index
    //! @return The center of corresponding bin of the axis
    double getYaxisValue(size_t globalbin);

    //! Returns content (accumulated value) of the bin with given index.
    //! @param globalbin The global bin index
    //! @return The value accumulated by the bin (integral)
    double getBinContent(size_t globalbin) const;

    //! Returns content (accumulated value) of the bin with given indices (for 2D histograms).
    //! @param binx x-axis bin index
    //! @param biny y-axis bin index
    //! @return The value accumulated by the bin (integral)
    double getBinContent(size_t binx, size_t biny) const;

    //! Sets content of the bin corresponding to the globalbin number
    void setBinContent(size_t globalbin, double value);

    //! Add the value to the bin
    void addBinContent(size_t globalbin, double value);

    //! Returns error of the bin with given index.
    double getBinError(size_t globalbin) const;

    //! Returns error of the bin with given indices (for 2D histograms).
    double getBinError(size_t binx, size_t biny) const;

    //! Returns average value in the bin with given index.
    double getBinAverage(size_t globalbin) const;

    //! Returns average value of the bin with given indices (for 2D histograms).
    double getBinAverage(size_t binx, size_t biny) const;

    //! Returns number of entries in the bin with given index.
    int getBinNumberOfEntries(size_t globalbin) const;

    //! Returns number of entries in the bin with given indices (for 2D histograms).
    int getBinNumberOfEntries(size_t binx, size_t biny) const;

    //! Returns histogram maximum value (maximum of getBinContent() over all bins)
    double getMaximum() const;

    //! Returns globalbin index with maximum content
    size_t getMaximumBinIndex() const;

    //! Returns histogram minimum value (minimum of getBinContent() over all bins)
    double getMinimum() const;

    //! Returns globalbin index with minimum content
    size_t getMinimumBinIndex() const;

    //! Multiply this histogram (every bin content value) by a constant
    void scale(double value);

    //! Returns integral of bins content (computed as a sum of all bin content).
    double integral() const;

//    double& operator[](size_t index);
//    const double& operator[](size_t index) const;


#ifdef BORNAGAIN_PYTHON
    //! Returns numpy array with bin content (accumulated values)
    PyObject *getArray(DataType dataType = INTEGRAL) const;
#endif

    //! Reset histogram content (axes remains)
    void reset();

    static IHistogram *createHistogram(const OutputData<double> &source);

    //! creates new OutputData with histogram's shape and put there values corresponding to DataType
    OutputData<double> *createOutputData(DataType dataType = INTEGRAL) const;

    //! Returns true if objects a) have same dimensions b) bin boundaries of axes coincide
    bool hasSameShape(const IHistogram& other) const;

    //! Returns true if object have same dimensions and number of axes bins
    bool hasSameDimensions(const IHistogram& other) const;

    //! addition-assignment operator for two histograms
    const IHistogram& operator+=(const IHistogram& right);


protected:
    void check_x_axis() const;
    void check_y_axis() const;
    void init_from_data(const OutputData<double> &source);
    double getBinData(size_t globalbin, DataType dataType) const;
    std::vector<double> getDataVector(DataType dataType) const;
    OutputData<CumulativeValue> m_data;
};

#endif
