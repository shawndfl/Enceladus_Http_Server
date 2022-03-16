/*
 * UriFormater.cc
 *
 *  Created on: Jan 30, 2022
 *      Author: shawn
 */

#include "UnitTest++/UnitTest++.h"
#include "Enceladus.h"
#include <bitset>
#include <sstream>
#include <iomanip>      // std::setfill, std::setw

SUITE(UriFormater) {

TEST(sha1) {
   ehs::SHA1 sha1;
   std::string response = "dGhlIHNhbXBsZSBub25jZQ==258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
   sha1.Input(response.c_str(), response.size());

   unsigned char dig[20];
   sha1.Result((unsigned*)dig);

   std::stringstream debug;

   size_t count =  sizeof(dig);
   LOGD("count " << count);
   for(size_t i = 0; i < count; i++) {
      debug << " 0x" << std::setw(2) << std::setfill('0') << std::hex << (unsigned )(dig[i]);
   }

   std::string expected =" 0xb3 0x7a 0x4f 0x2c 0xc0 0x62 0x4f 0x16 0x90 0xf6 0x46 0x06 0xcf 0x38 0x59 0x45 0xb2 0xbe 0xc4 0xea";
   CHECK_EQUAL(expected,  debug.str());

   std::string encoding = ehs::Base64::encode((char*)dig, count);
   expected = "s3pPLMBiTxaQ9kYGzzhZRbK+xOo=";
   CHECK_EQUAL(expected, encoding);
}

TEST(base64DecodeErrors) {

   std::vector<char> binary;

   // Not a multiple of 4
   CHECK_EQUAL(false, ehs::Base64::decode("AB", binary));

   // invalid character
   CHECK_EQUAL(false, ehs::Base64::decode("ABC!", binary));

   // too much padding
   CHECK_EQUAL(false, ehs::Base64::decode("ABC===", binary));
}

TEST(base64Empty) {
   std::string data;

   std::string encoded = ehs::Base64::encode(data.c_str(), data.size());
   CHECK_EQUAL("", encoded);

   std::vector<char> binary;
   ehs::Base64::decode(encoded, binary);

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

   std::string encoded = ehs::Base64::encode(data.c_str(), data.size());
   CHECK_EQUAL("VVU=", encoded);

   std::vector<char> binary;
   ehs::Base64::decode(encoded, binary);

   CHECK_EQUAL(data.size(), binary.size());

   for(size_t i =0; i < binary.size(); i++) {
      CHECK_EQUAL(data[i], binary[i]);
   }
}

TEST(base64Encoding2) {
   std::string data = "Testing";
   std::string encoded = ehs::Base64::encode(data.c_str(), data.size());

   CHECK_EQUAL("VGVzdGluZw==", encoded);
   std::vector<char> binary;
   ehs::Base64::decode(encoded, binary);

   CHECK_EQUAL(data.size(), binary.size());

   for(size_t i =0; i < binary.size(); i++) {
      CHECK_EQUAL(data[i], binary[i]);
   }
}

TEST(base64Encoding3) {
   std::string data = "Some really long string";
   std::string encoded = ehs::Base64::encode(data.c_str(), data.size());

   CHECK_EQUAL("U29tZSByZWFsbHkgbG9uZyBzdHJpbmc=", encoded);
   std::vector<char> binary;
   ehs::Base64::decode(encoded, binary);

   CHECK_EQUAL(data.size(), binary.size());

   for(size_t i =0; i < binary.size(); i++) {
      CHECK_EQUAL(data[i], binary[i]);
   }
}

TEST(InitTest) {
   ehs::RequestFormater formater;
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

