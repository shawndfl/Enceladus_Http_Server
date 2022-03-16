/*
 * Base64.cc
 *
 *  Created on: Feb 13, 2022
 *      Author: shawn
 */

#include "Base64.h"
#include "Logging.h"
#include <bitset>

namespace ehs {
const char* Encoding = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz"
      "0123456789+/";

const char Decode[] = {
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
    0x64, 0x64, 0x64, 0x3E, 0x64, 0x64, 0x64, 0x3F, 0x34, 0x35,
    0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x64, 0x64,
    0x64, 0x00, 0x64, 0x64, 0x64, 0x00, 0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
    0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    0x19, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x1A, 0x1B, 0x1C,
    0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26,
    0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
    0x31, 0x32, 0x33, 0x64, 0x64, 0x64, 0x64, 0x64};

const char Padding = '=';

/*************************************************/
Base64::Base64() {

}

/*************************************************/
Base64::~Base64() {

}

/*************************************************/
std::string Base64::encode(const char *data, size_t size) {
   std::string encode;
   // step 3 bytes at a time
   for (size_t i = 0; i < size; i += 3) {

      unsigned char byte1;
      unsigned char byte2;
      unsigned char byte3;
      uint pad;

      if (i + 1 >= size) {
         byte1 = data[i + 0];
         byte2 = 0x0;
         byte3 = 0x0;
         pad = 2;
      } else if (i + 2 >= size) {
         byte1 = data[i + 0];
         byte2 = data[i + 1];
         byte3 = 0x0;
         pad = 1;
      } else {
         byte1 = data[i + 0];
         byte2 = data[i + 1];
         byte3 = data[i + 2];
         pad = 0;
      }

      uint const concatBits = (byte1 << 16) | (byte2 << 8) | byte3;
      ushort index1 = (concatBits >> 18)    & 0x3F;
      ushort index2 = (concatBits >> 12)    & 0x3F;
      ushort index3 = (concatBits >> 6)     & 0x3F;
      ushort index4 = (concatBits)          & 0x3F;

      if (pad == 2) {
         encode += Encoding[index1];
         encode += Encoding[index2];
         encode += Padding;
         encode += Padding;
      } else if (pad == 1) {
         encode += Encoding[index1];
         encode += Encoding[index2];
         encode += Encoding[index3];
         encode += Padding;
      } else {
         encode += Encoding[index1];
         encode += Encoding[index2];
         encode += Encoding[index3];
         encode += Encoding[index4];
      }

   }
   return encode;
}

/*************************************************/
bool isValidCharacter(char ch) {
   bool good = (ch >='A' && ch <='Z') ||
               (ch >='a' && ch <='z') ||
               (ch >='0' && ch <='9') ||
               (ch =='/' && ch =='+') ||
               ch == Padding;
   return good;
}

/*************************************************/
bool Base64::decode(const std::string &encoded, std::vector<char>& decoded) {

   uint encodedSize = encoded.size();

   // check size
   if(encodedSize%4 != 0) {
      LOGD("Invalid base64 string " << encoded);
      return false;
   }

   std::string encode;
   int paddingCount = 0;
   // step 3 bytes at a time
   for (size_t i = 0; i < encodedSize; i += 4) {

      if (!isValidCharacter(encoded[i])) {
         LOGD("Invalid base64 char at " << i << ": " << encoded);
         return false;
      }
      if (!isValidCharacter(encoded[i+1])) {
         LOGD("Invalid base64 char at " << i+1 << ": " << encoded);
         return false;
      }
      if (!isValidCharacter(encoded[i+2])) {
         LOGD("Invalid base64 char at " << i+2 << ": " << encoded);
         return false;
      }
      if (!isValidCharacter(encoded[i+3])) {
         LOGD("Invalid base64 char at " << i+3 << ": " << encoded);
         return false;
      }

      uint const concat_bytes =
              (Decode[(int)encoded[i]]   << 18) |
              (Decode[(int)encoded[i+1]] << 12) |
              (Decode[(int)encoded[i+2]] << 6)  |
               Decode[(int)encoded[i+3]];

      unsigned char byte1 = (concat_bytes >> 16) & 0b1111'1111;
      unsigned char byte2 = (concat_bytes >> 8) & 0b1111'1111;
      unsigned char byte3 = concat_bytes & 0b1111'1111;

      decoded.push_back(byte1);

      // check for padding
      if((int)encoded[i+2] != Padding) {
         decoded.push_back(byte2);
      } else {
         paddingCount++;
      }

      // check for padding
      if((int)encoded[i+3] != Padding) {
         decoded.push_back(byte3);
      } else {
         paddingCount++;
      }
   }

   // check to be sure the encoded string does not have more than two "=="
   if(paddingCount > 2) {
      LOGD("Invalid base64 string. Too much padding " << encoded);
      return false;
   }

   return true;
}
}
