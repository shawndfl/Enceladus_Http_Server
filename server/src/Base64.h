/*
 * Base64.h
 *
 *  Created on: Feb 13, 2022
 *      Author: shawn
 */

#ifndef SRC_BASE64_H_
#define SRC_BASE64_H_

#include <string>
#include <vector>

/**
 * This class will encode and decode base 64 string
 */
class Base64 {
public:
   Base64();
   virtual ~Base64();

   /**
    * Encode the string
    */
   static std::string encode(const char* data, size_t size);

   /**
    * Decode the string
    */
   static  bool decode(const std::string& encoded,  std::vector<char>& decoded);
};

#endif /* SRC_BASE64_H_ */
