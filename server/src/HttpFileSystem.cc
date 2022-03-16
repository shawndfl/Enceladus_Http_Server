/*
 * HttpFileSystem.cc
 *
 *  Created on: Jun 6, 2020
 *      Author: sdady
 */

#include "HttpFileSystem.h"
#include "fstream"
#include "Logging.h"
#include <sys/stat.h>
#include <unistd.h>

namespace ehs {

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
   size_t dot = path.find_last_of('.');
   size_t slash = path.find_last_of('/');

   if(dot < slash) {
      dot = std::string::npos;
   }

   if(dot != std::string::npos) {
      return path.substr(dot);
   } else {
      return "";
   }
}

/*************************************************/
bool HttpFileSystem::exists(const std::string& filename) {
   struct stat st;
   if(stat(filename.c_str(), &st) != -1) {
      if((st.st_mode & S_IFMT) == S_IFREG) {
         return true;
      }
   }
   return false;
}
}
