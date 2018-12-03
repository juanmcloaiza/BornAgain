// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUIPerformanceTest/GUIPerformanceTest.h
//! @brief     Defines GUI performance functional test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef CSVIMPORTASSISTANTUSECASES_H
#define CSVIMPORTASSISTANTUSECASES_H

#include "IFunctionalTest.h"
#include "SpecularDataItem.h"
#include "AxisNames.h"
#include <QString>
#include <memory>

//! Functional test to measure performance of CsvImportAssistant by loading files of different sizes
class CsvImportAssistantUseCases : public IFunctionalTest
{
public:
    CsvImportAssistantUseCases();
    ~CsvImportAssistantUseCases();

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
    std::vector<double> m_expCoords{10.,20.,30.,40.,50.,60.,70.,80.,90.,100.};
    std::vector<double> m_expIntens{1.,.9,.8,.7,.6,.5,.4,.3,.2,.1};
    double m_coordinateMultiplier = 10.0;
    double m_intensityMultiplier = 0.1;
    AxesUnits m_units = AxesUnits::RADIANS;


private:
};

#endif // CSVIMPORTASSISTANTUSECASES_H
