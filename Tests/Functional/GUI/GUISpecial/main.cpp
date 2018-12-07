// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUISpecial/main.cpp
//! @brief     Implements main to run GUI special tests.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUISpecialTestFactory.h"
#include "TestService.h"
#include <QCoreApplication>

//! Runs PyEmbedded functional test.
int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);

    std::string testName = ""; //"CsvImportAssistantUseCases"

    if (testName.empty()) {
        return TestService<GUISpecialTestFactory>().execute(argc, argv) ? 0 : 1;
    } else {
        return TestService<GUISpecialTestFactory>().execute(testName) ? 0 : 1;
    }
}
