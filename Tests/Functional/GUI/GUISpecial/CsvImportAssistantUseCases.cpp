// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUISpecial/GUIUseCases.cpp
//! @brief     Implements Import Assistant functional test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "CsvImportAssistantUseCases.h"
#include "ArrayUtils.h"
#include "AxisNames.h"
#include "CsvImportAssistant.h"
#include "JobItemUtils.h"
#include "OutputDataReadFactory.h"
#include "OutputDataWriteFactory.h"
//#include <QDebug>
#include "BATesting.h"
#include <FileSystemUtils.h>
#include <ctime>
#include <iostream>

namespace
{
std::string path(const std::string fileName)
{
    return FileSystemUtils::jointPath(BATesting::ReflectivityReferenceDir(), fileName);
}
std::string vectorToString(std::vector<double> X)
{
    std::stringstream buffer;
    buffer << "{ ";
    for (auto x : X)
        buffer << x << ",";
    buffer << " }";
    return buffer.str();
}
template <class T> bool areVectorsEqual(std::vector<T>& X, std::vector<T>& Y)
{
    if (X.size() != Y.size())
        return false;
    size_t size = X.size();
    for (size_t t = 0; t < size; ++t)
        if (fabs(X[t] - Y[t]) > 1e-14) {
            std::cout << Y[t] - X[t] << std::endl;
            return false;
        }
    return true;
}
}

bool CsvImportAssistantUseCases::runTest()
{
    std::cout << "CsvImportAssistantUseCases -> Running ..." << std::endl;

    for (auto thisFile : m_dataFileParameters) {
        std::cout << "----- File: " << thisFile.filename << " -----" << std::endl;

        const QString f = QString::fromStdString(path(thisFile.filename));
        CsvImportAssistant assistant(f);

        assistant.setFirstRow(thisFile.firstRow);
        assistant.setLastRow(thisFile.lastRow);
        assistant.setCoordinateColumn(thisFile.coordinateColumn, m_units, m_coordinateMultiplier);
        assistant.setIntensityColumn(thisFile.intensityColumn, m_intensityMultiplier);

        ImportDataInfo currentData = assistant.getData();
        if (!currentData) {
            std::cout << "Empty Data!" << std::endl;
            if (thisFile.filename == "NonExistentFile") {
                std::cout << "...it is ok in this case." << std::endl;
                continue;
            }
            return false;
        }

        auto iData_ptr = currentData.intensityData();
        if (!iData_ptr) {
            std::cout << "No intensity data!" << std::endl;
            return false;
        }

        size_t AllocSize = iData_ptr->getAllocatedSize();
        size_t expectedAllocSize = size_t(1 + thisFile.lastRow - thisFile.firstRow);

        size_t DataRank = currentData.dataRank();
        size_t expectedDataRank = 1;

        auto CoordinateValues = iData_ptr->getAxis(0).getBinCenters();
        const std::vector<double> expectedCoordVals = thisFile.expectedCoordinateValues;

        auto IntensityValues = iData_ptr->getRawDataVector();
        std::vector<double> expectedIntensVals = thisFile.expectedIntensityValues;

        auto UnitsLabel = currentData.unitsLabel();
        auto expectedUnitsLabel = JobItemUtils::nameFromAxesUnits(m_units);

        auto AxisLabel0 = assistant.getData().axisLabel(0);
        auto expectedAxisLabel0 = QString::fromStdString(AxisNames::InitSpecAxis()[m_units]);

        auto AxisLabel1 = assistant.getData().axisLabel(1);
        auto expectedAxisLabel1 = SpecularDataAxesNames::y_axis_default_name;

        std::cout << "Data Rank: " << DataRank << "; Expected: " << expectedDataRank << std::endl;
        std::cout << "Alloc Size: " << AllocSize << "; Expected: " << expectedAllocSize
                  << std::endl;
        std::cout << "Intensity Values: " << vectorToString(IntensityValues)
                  << "; Expected: " << vectorToString(expectedIntensVals) << std::endl;
        std::cout << "Coordinate Values: " << vectorToString(CoordinateValues)
                  << "; Expected: " << vectorToString(expectedCoordVals) << std::endl;
        std::cout << "Units Label: " << UnitsLabel.toStdString()
                  << "; Expected: " << expectedUnitsLabel.toStdString() << std::endl;
        std::cout << "Axis Label 0: " << AxisLabel0.toStdString()
                  << "; Expected: " << expectedAxisLabel0.toStdString() << std::endl;
        std::cout << "Axis Label 1: " << AxisLabel1.toStdString()
                  << "; Expected: " << expectedAxisLabel1.toStdString() << std::endl;

        if (DataRank != expectedDataRank)
            return false;

        if (AllocSize != expectedAllocSize)
            return false;

        if (CoordinateValues != expectedCoordVals)
            return false;

        if (!areVectorsEqual(IntensityValues, expectedIntensVals))
            return false;

        if (UnitsLabel != expectedUnitsLabel)
            return false;

        if (AxisLabel0 != expectedAxisLabel0)
            return false;

        if (AxisLabel1 != expectedAxisLabel1)
            return false;

        std::cout << "---------------------------------------------" << std::endl;
    }
    return true;
}
