
#include <string>
#include "Logging.h"
#include "UnitTest++/TestReporterStdout.h"
#include "UnitTest++/UnitTest++.h"
#include <map>
#include <iostream>

int main(int argc, const char *argv[]) {
	UnitTest::TestReporterStdout reporter;
	UnitTest::TestRunner runner(reporter);
	const UnitTest::TestList& list = UnitTest::Test::GetTestList();

	UnitTest::TestList newList;

	// list of all suites
	std::map<std::string, int> suites;

	// only run one suite
	if(argc > 1) {
		std::string suite = argv[1];
		UnitTest::Test *curTest = list.GetHead();

		while (curTest != 0) {

			std::string currentSuite = curTest->m_details.suiteName;
			// keep track of the suites
			suites[currentSuite]++;

			// if this matches the filter add it to the new list
			if(currentSuite == suite) {
				newList.Add(curTest);
			}
			curTest = curTest->m_nextTest;
		}
	} else {

		// run all tests
		newList = list;
	}

	if(newList.GetHead() == nullptr) {

		std::cout << "Select one of the suites:\n";
		for(auto pair: suites) {
			std::cout << "  " << pair.first << "\n";
		}
		return 1;
	} else {

		// run the tests
		return runner.RunTestsIf(newList, NULL, UnitTest::True(), 0);
	}
}
