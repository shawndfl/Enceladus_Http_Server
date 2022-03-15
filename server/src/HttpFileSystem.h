/*
 * HttpFileSystem.h
 *
 *  Created on: Jun 6, 2020
 *      Author: sdady
 */

#ifndef SRC_HTTPFILESYSTEM_H_
#define SRC_HTTPFILESYSTEM_H_

#include <string>

class HttpFileSystem {
public:
   HttpFileSystem();
   virtual ~HttpFileSystem();

   static std::string getExtenion(const std::string& path);

   static bool exists(const std::string& file);

   static std::string toLower(const std::string& text);

};

#endif /* SRC_HTTPFILESYSTEM_H_ */
