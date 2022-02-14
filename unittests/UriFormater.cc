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
#include "Base64.h"
#include <bitset>

SUITE(UriFormater) {

TEST(base64DecodeErrors) {

   std::vector<char> binary;

   // Not a multiple of 4
   CHECK_EQUAL(false, Base64::decode("AB", binary));

   // invalid character
   CHECK_EQUAL(false, Base64::decode("ABC!", binary));

   // too much padding
   CHECK_EQUAL(false, Base64::decode("ABC===", binary));
}

TEST(base64Empty) {
   std::string data;

   std::string encoded = Base64::encode(data.c_str(), data.size());
   CHECK_EQUAL("", encoded);

   std::vector<char> binary;
   Base64::decode(encoded, binary);

   CHECK_EQUAL(data.size(), binary.size());

   for(size_t i =0; i < binary.size(); i++) {
      CHECK_EQUAL(data[i], binary[i]);
   }
}

TEST(base64Encoding) {
   std::string data;
   data.resize(2);
   data.data()[0] = 0b01010101;
   data.data()[1] = 0b01010101;

   std::string encoded = Base64::encode(data.c_str(), data.size());
   CHECK_EQUAL("VVU=", encoded);

   std::vector<char> binary;
   Base64::decode(encoded, binary);

   CHECK_EQUAL(data.size(), binary.size());

   for(size_t i =0; i < binary.size(); i++) {
      CHECK_EQUAL(data[i], binary[i]);
   }
}

TEST(base64Encoding2) {
   std::string data = "Testing";
   std::string encoded = Base64::encode(data.c_str(), data.size());

   CHECK_EQUAL("VGVzdGluZw==", encoded);
   std::vector<char> binary;
   Base64::decode(encoded, binary);

   CHECK_EQUAL(data.size(), binary.size());

   for(size_t i =0; i < binary.size(); i++) {
      CHECK_EQUAL(data[i], binary[i]);
   }
}

TEST(base64Encoding3) {
   std::string data = "Some really long string";
   std::string encoded = Base64::encode(data.c_str(), data.size());

   CHECK_EQUAL("U29tZSByZWFsbHkgbG9uZyBzdHJpbmc=", encoded);
   std::vector<char> binary;
   Base64::decode(encoded, binary);

   CHECK_EQUAL(data.size(), binary.size());

   for(size_t i =0; i < binary.size(); i++) {
      CHECK_EQUAL(data[i], binary[i]);
   }
}


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


