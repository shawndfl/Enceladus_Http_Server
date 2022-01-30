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
   path = formater.getResourcePath("/opt//test", "http");
   LOG("path " << path);

   path = formater.getResourcePath("/opt/../test//", "http");
   LOG("path " << path);

   path = formater.getResourcePath("/opt/../../../test", "http");
   LOG("path " << path);
}
}


