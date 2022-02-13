/*
 * HttpFileSystem.cc
 *
 *  Created on: Jun 6, 2020
 *      Author: sdady
 */

#include "HttpFileSystem.h"
#include "fstream"
#include "Logging.h"
#include <unistd.h>

/*************************************************/
HttpFileSystem::HttpFileSystem() {

}

/*************************************************/
HttpFileSystem::~HttpFileSystem() {
}

/*************************************************/
std::string HttpFileSystem::toLower(const std::string& text) {
   std::string lower;
   for(size_t i = 0; i < text.size(); i++) {
      lower += std::tolower(text[i]);
   }
   return lower;
}

/*************************************************/
std::string HttpFileSystem::getExtenion(const std::string& path) {
   size_t offset = path.find_last_of('.');
   if(offset != std::string::npos) {
      return path.substr(offset);
   } else {
      return "";
   }
}

/*************************************************/
bool HttpFileSystem::exists(const std::string& filename) {
   if (FILE *file = fopen(filename.c_str(), "r")) {
          fclose(file);
          return true;
      } else {
          return false;
      }
}
