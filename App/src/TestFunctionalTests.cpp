#include "TestFunctionalTests.h"
#include "ProgramOptions.h"
#include "IsGISAXSTools.h"
#include "OutputDataFunctions.h"
#include <iostream>
#include <vector>
#include <string>


void TestFunctionalTests::execute()
{
    if(!readTestNames()) return;

    for(size_t i=0; i<m_testNames.size(); ++i) {
        FunctionalTest_t test = m_testRegistry.getTest(m_testNames[i]);
        test->runTest();
        test->analyseResults();

//        double diff = OutputDataFunctions::GetDifference(*test->getResult(), *test->getReference());
//        std::cout << "XXX " << diff << std::endl;

//        for(size_t j=0; j<test->getResult()->getAllocatedSize(); ++j) {
//            std::cout << "AAA " << j << " " << (*test->getResult())[j]
//                         << " " << (*test->getReference())[j]
//                         << " diff:" << ((*test->getResult())[j] - (*test->getReference())[j])/(*test->getReference())[j]
//                            << std::endl;
//        }

        IsGISAXSTools::drawOutputDataComparisonResults( *test->getResult(),
            *test->getReference(), test->getName(), test->getDescription());
   }
}


bool TestFunctionalTests::readTestNames()
{
    if (mp_options->find("functest")) {
        m_testNames = (*mp_options)["functest"].as<std::vector<std::string> >();
    }

    bool areCorrectNames(true);
    if(m_testNames.empty()) {
        std::cout << std::endl << "TestFunctionalTest::readTestNames() -> Info. No tests specified. Select one or more from list below." << std::endl;
        areCorrectNames = false;
    }

    for(size_t i=0; i<m_testNames.size(); ++i) {
        if(!m_testRegistry.isRegisteredName(m_testNames[i])) {
            std::cout << "TestFunctionalTest::readTestNames() -> Info. Not registered test with name '" << m_testNames[i] << "'." << std::endl;
            areCorrectNames = false;
        }
    }

    if(areCorrectNames) {
        return true;
    } else {
        m_testRegistry.printCatalogue();
        std::cout << std::endl;
        return false;
    }
}