// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUIUseCases/GUIUseCases.cpp
//! @brief     Implements GUI performance functional test.
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
    for(auto x : X)
        buffer << x << ",";
    buffer << " }";
    return buffer.str();
}
template<class T>
bool areVectorsEqual(std::vector<T> &X, std::vector<T> &Y){
    if(X.size() != Y.size())
        return false;
    size_t size = X.size();
    for(size_t t = 0; t < size ; ++t)
        if(fabs(X[t] - Y[t]) > 1e-14){
            std::cout << Y[t] - X[t] << std::endl;
            return false;
        }
    return true;

}
}

CsvImportAssistantUseCases::CsvImportAssistantUseCases()
{
    m_dataFileParameters = {
        //{"filename", firstRow, lastRow, coordinateColumn, intensityColumn, expCoords, expIntens},
//        {"probeA_merged.txt", m_firstRow, m_lastRow, m_coordinateColumn, m_intensityColumn, m_expCoords, m_expIntens},
//        {"mg6c_Merged.txt", m_firstRow, m_lastRow, m_coordinateColumn, m_intensityColumn, m_expCoords, m_expIntens},
//        {"raw_data_MG-6a-XRR-Standard_0-1_5deg-step1-2.csv", m_firstRow, m_lastRow, m_coordinateColumn, m_intensityColumn, m_expCoords, m_expIntens},
//        {"mg6c_Merged.png", m_firstRow, m_lastRow, m_coordinateColumn, m_intensityColumn, m_expCoords, m_expIntens},
//        {"Cut_2.dat", m_firstRow, m_lastRow, m_coordinateColumn+2, m_intensityColumn, m_expCoords, m_expIntens},
//        {"Cut_1.dat", m_firstRow, m_lastRow, m_coordinateColumn+2, m_intensityColumn, m_expCoords, m_expIntens},
//        {"p12537_00000125.dat", 200+m_firstRow, 200+m_lastRow, m_coordinateColumn, m_intensityColumn+5, m_expCoords, m_expIntens},
//        {"p12537_00000128.dat", 200+m_firstRow, 200+m_lastRow, m_coordinateColumn, m_intensityColumn+5, m_expCoords, m_expIntens},
//        {"p15145_00005044.dat", 200+m_firstRow, 200+m_lastRow, m_coordinateColumn, m_intensityColumn+9, m_expCoords, m_expIntens},
//        {"p15145_00005023.dat", 200+m_firstRow, 200+m_lastRow, m_coordinateColumn, m_intensityColumn+13, m_expCoords, m_expIntens},
//        {"NR_System2_D2O_T20.DAT", m_firstRow, m_lastRow, m_coordinateColumn, m_intensityColumn+1, m_expCoords, m_expIntens},
//        {"R_d2o.txt", m_firstRow, m_lastRow, m_coordinateColumn, m_intensityColumn, m_expCoords, m_expIntens},
//        {"P_ME_305_D2O_15C_01.DAT", m_firstRow, m_lastRow, m_coordinateColumn+2, m_intensityColumn-1, m_expCoords, m_expIntens},
//        {"P_ME_3026_D2O_60C_05.DAT", m_firstRow, m_lastRow, m_coordinateColumn+2, m_intensityColumn-1, m_expCoords, m_expIntens},
        {"b_104.dat", m_firstRow, m_lastRow, m_coordinateColumn, m_intensityColumn, m_expCoords, m_expIntens},
    };
}

CsvImportAssistantUseCases::~CsvImportAssistantUseCases()
{
}

// ---
bool CsvImportAssistantUseCases::runTest()
{
    std::cout << "CsvImportAssistantPerformanceTest -> Running ..." << std::endl;
    bool testPassed = true;

    for (auto thisFile : m_dataFileParameters) {
        const QString f = QString::fromStdString(path(thisFile.filename));
        std::cout << f.toStdString() << std::endl;
        CsvImportAssistant assistant(f);

        assistant.setFirstRow(thisFile.firstRow);
        assistant.setLastRow(thisFile.lastRow);
        assistant.setCoordinateColumn(thisFile.coordinateColumn, m_units, m_coordinateMultiplier);
        assistant.setIntensityColumn(thisFile.intensityColumn, m_intensityMultiplier);

        ImportDataInfo currentData = assistant.getData();
        if(!currentData){
            std::cout << "Empty Data!" << std::endl;
            return false;
        }

        auto   iData_ptr = currentData.intensityData();
        if(!iData_ptr){
            std::cout << "No intensity data!" << std::endl;
            return false;
        }

        size_t AllocSize = iData_ptr->getAllocatedSize();
        size_t expectedAllocSize = size_t(1 + thisFile.lastRow - thisFile.firstRow);

        size_t DataRank = currentData.dataRank();
        size_t expectedDataRank = 1; //Reflectivity data is 1d, so rank is 1;

        auto CoordinateValues = iData_ptr->getAxis(0).getBinCenters();
        const std::vector<double> expectedCoordVals = thisFile.expectedCoordinateValues;

        auto IntensityValues = iData_ptr->getRawDataVector();
        IntensityValues.shrink_to_fit();
        std::vector<double> expectedIntensVals = thisFile.expectedIntensityValues;
        expectedIntensVals.shrink_to_fit();

        auto UnitsLabel = currentData.unitsLabel();
        auto expectedUnitsLabel = JobItemUtils::nameFromAxesUnits(m_units);

        auto AxisLabel0 = assistant.getData().axisLabel(0);
        auto expectedAxisLabel0 =
            QString::fromStdString(AxisNames::InitSpecAxis()[m_units]);

        auto AxisLabel1 = assistant.getData().axisLabel(1);
        auto expectedAxisLabel1 = SpecularDataAxesNames::y_axis_default_name;


        std::cout << "--------------------------------------------- " << std::endl;
//        std::cout << thisFile.filename
//                  << "\n"
//                  << thisFile.firstRow
//                  << "\n"
//                  << thisFile.lastRow
//                  << "\n"
//                  << thisFile.coordinateColumn
//                  << "\n"
//                  << thisFile.intensityColumn
//                  << "\n"
//                  << vectorToString(CoordinateValues)
//                  << "\n"
//                  << vectorToString(IntensityValues)
//                  << "\n"
//                  << UnitsLabel.toStdString()
//                  << "\n"
//                  << AxisLabel0.toStdString()
//                  << "\n"
//                  << AxisLabel1.toStdString()
//                  << "\n"
//                  << std::endl;


        std::cout << "----- File: " << thisFile.filename << " ----- " << std::endl;
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


    std::cout << "TEST PASSED!" << std::endl;
                if (DataRank != expectedDataRank)
                    return false;

    std::cout << "TEST PASSED!" << std::endl;
                if (AllocSize != expectedAllocSize)
                    return false;
    std::cout << "TEST PASSED!" << std::endl;

                if (CoordinateValues != expectedCoordVals)
                    return false;

    std::cout << "TEST PASSED!" << std::endl;
                if (!areVectorsEqual(IntensityValues, expectedIntensVals))
                    return false;

    std::cout << "TEST PASSED!" << std::endl;
                if (UnitsLabel != expectedUnitsLabel)
                    return false;

    std::cout << "TEST PASSED!" << std::endl;
                if (AxisLabel0 != expectedAxisLabel0)
                    return false;

    std::cout << "TEST PASSED!" << std::endl;
                if (AxisLabel1 != expectedAxisLabel1)
                    return false;
    }
    std::cout << "TEST PASSED!" << std::endl;
    return testPassed;
}
