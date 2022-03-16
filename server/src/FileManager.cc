/*
 * FileManager.cc
 *
 *  Created on: Feb 11, 2022
 *      Author: shawn
 */

#include "FileManager.h"
#include <fstream>

namespace ehs {

/*************************************************/
FileManager::FileManager() {

}

/*************************************************/
FileManager::~FileManager() {

}

/*************************************************/
bool FileManager::loadFile(const std::string path) {
   std::ifstream stream;
   stream.open(path);
   if(stream.is_open()) {
      content_.assign(std::istreambuf_iterator<char>(stream),
                        std::istreambuf_iterator<char>()) ;
      stream.close();
      return true;
   } else {
      content_ = "";
      return false;
   }
}

/*************************************************/
const std::string& FileManager::getContent() const {
   return content_;
}
}
