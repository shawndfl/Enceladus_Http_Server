/*
 * UriFormater.cc
 *
 *  Created on: Jan 30, 2022
 *      Author: shawn
 */

#include "UnitTest++/UnitTest++.h"
#include "Logging.h"
#include "RequestFormater.h"
#include "JsonParser.h"

SUITE(UriFormater) {

TEST(InitTest) {
   RequestFormater formater;
   std::string path;
   path = formater.getResourcePath("./../UnitTest++", "Checks.h");
   CHECK(path.size() > 0);

   path = formater.getResourcePath("./../UnitTest++", "../..//makefile");
   CHECK(path.size() == 0);

   path = formater.getResourcePath("./../UnitTest++", "missing_file");
   CHECK(path.size() == 0);

   path = formater.getResourcePath("./", "unit_tests");
   CHECK(path.size() > 0);
}
}


