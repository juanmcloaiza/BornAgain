// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUISpecial/GUIUseCases.cpp
//! @brief     Defines Import Assistant functional test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef CSVIMPORTASSISTANTUSECASES_H
#define CSVIMPORTASSISTANTUSECASES_H

#include "AxisNames.h"
#include "IFunctionalTest.h"
#include "SpecularDataItem.h"
#include <QString>
#include <memory>

//! Functional test to measure performance of CsvImportAssistant by loading files of different sizes
class CsvImportAssistantUseCases : public IFunctionalTest
{
public:
    CsvImportAssistantUseCases()
    {
        m_dataFileParameters = {
                //{"unqualified_filename",
                //firstRow,
                //lastRow,
                //coordinateColumn,
                //intensityColumn,
                //expectedCoords,
                //expectedIntensities},

                {"probeA_merged.txt",
                 m_firstRow,
                 m_lastRow,
                 m_coordinateColumn,
                 m_intensityColumn,
                 m_expCoords,
                 m_expIntens},

                {"mg6c_Merged.txt",
                 m_firstRow,
                 m_lastRow,
                 m_coordinateColumn,
                 m_intensityColumn,
                 m_expCoords,
                 m_expIntens},

                {"raw_data_MG-6a-XRR-Standard_0-1_5deg-step1-2.csv",
                 m_firstRow,
                 m_lastRow,
                 m_coordinateColumn,
                 m_intensityColumn,
                 m_expCoords,
                 m_expIntens},

                {"NonExistentFile",
                 m_firstRow,
                 m_lastRow,
                 m_coordinateColumn,
                 m_intensityColumn,
                 m_expCoords,
                 m_expIntens},

                {"Cut_2.dat",
                 m_firstRow,
                 m_lastRow,
                 m_coordinateColumn + 2,
                 m_intensityColumn,
                 m_expCoords,
                 m_expIntens},

                {"Cut_1.dat",
                 m_firstRow,
                 m_lastRow,
                 m_coordinateColumn + 2,
                 m_intensityColumn,
                 m_expCoords,
                 m_expIntens},

                {"p12537_00000125.dat",
                 200 + m_firstRow,
                 200 + m_lastRow,
                 m_coordinateColumn,
                 m_intensityColumn + 5,
                 m_expCoords,
                 m_expIntens},

                {"p12537_00000128.dat",
                 200 + m_firstRow,
                 200 + m_lastRow,
                 m_coordinateColumn,
                 m_intensityColumn + 5,
                 m_expCoords,
                 m_expIntens},

                {"p15145_00005044.dat",
                 200 + m_firstRow,
                 200 + m_lastRow,
                 m_coordinateColumn,
                 m_intensityColumn + 9,
                 m_expCoords,
                 m_expIntens},

                {"p15145_00005023.dat",
                 200 + m_firstRow,
                 200 + m_lastRow,
                 m_coordinateColumn,
                 m_intensityColumn + 13,
                 m_expCoords,
                 m_expIntens},

                {"NR_System2_D2O_T20.DAT",
                 m_firstRow,
                 m_lastRow,
                 m_coordinateColumn,
                 m_intensityColumn + 1,
                 m_expCoords,
                 m_expIntens},

                {"R_d2o.txt",
                 m_firstRow,
                 m_lastRow,
                 m_coordinateColumn,
                 m_intensityColumn,
                 m_expCoords,
                 m_expIntens},

                {"P_ME_305_D2O_15C_01.DAT",
                 m_firstRow,
                 m_lastRow,
                 m_coordinateColumn + 2,
                 m_intensityColumn - 1,
                 m_expCoords,
                 m_expIntens},

                {"P_ME_3026_D2O_60C_05.DAT",
                 m_firstRow,
                 m_lastRow,
                 m_coordinateColumn + 2,
                 m_intensityColumn - 1,
                 m_expCoords,
                 m_expIntens},

                {"b_104.dat",
                 m_firstRow,
                 m_lastRow,
                 m_coordinateColumn,
                 m_intensityColumn,
                 m_expCoords,
                 m_expIntens},
        };
    }
    ~CsvImportAssistantUseCases() {}

protected:
    struct datafile {
        std::string filename;
        int firstRow;
        int lastRow;
        int coordinateColumn;
        int intensityColumn;
        std::vector<double> expectedCoordinateValues;
        std::vector<double> expectedIntensityValues;
    };

    bool runTest();
    std::vector<datafile> m_dataFileParameters;
    int m_firstRow = 51;
    int m_lastRow = 60;
    int m_coordinateColumn = 1;
    int m_intensityColumn = 2;
    std::vector<double> m_expCoords{10., 20., 30., 40., 50., 60., 70., 80., 90., 100.};
    std::vector<double> m_expIntens{1., .9, .8, .7, .6, .5, .4, .3, .2, .1};
    double m_coordinateMultiplier = 10.0;
    double m_intensityMultiplier = 0.1;
    AxesUnits m_units = AxesUnits::RADIANS;

private:
};

#endif // CSVIMPORTASSISTANTUSECASES_H
