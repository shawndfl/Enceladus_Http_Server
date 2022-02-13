/*
 * FileManager.h
 *
 *  Created on: Feb 11, 2022
 *      Author: shawn
 */

#ifndef SRC_FILEMANAGER_H_
#define SRC_FILEMANAGER_H_

#include <string>

/**
 * This class is used to load a file into memory
 */
class FileManager {
public:
   FileManager();
   virtual ~FileManager();

   bool loadFile(const std::string path);

   const std::string& getContent() const;

private:
   std::string content_;
};

#endif /* SRC_FILEMANAGER_H_ */
