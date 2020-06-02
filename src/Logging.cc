
#include "Logging.h"

#include <chrono>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <sstream>
#include <iostream>
#include <iomanip>

/*************************************************/
Logging::Logging() {
}

/*************************************************/
Logging::~Logging() {
}

/*************************************************/
void Logging::timestamp(char* outTimestamp, int len)
{
    time_t ltime; /* calendar time */
    ltime=time(NULL); /* get current cal time */
    struct tm* time = localtime(&ltime);
    sprintf(outTimestamp, "%d:%d:%d", time->tm_hour, time->tm_min, time->tm_sec );
}


/*************************************************/
void Logging::logit(const char logType,
      const std::string& file,
      int line,
      const std::string& text) {

   auto t = std::chrono::high_resolution_clock::now();
   std::time_t time = std::chrono::system_clock::to_time_t(t);
   std::tm* now = std::localtime(&time);

   const int fileSize = 20;
   std::string filename;
   if(file.size() > fileSize - 3) {
      filename = "..." + file.substr(file.size() - (fileSize -3) );
   } else {
      filename = file;
   }

   std::cout << logType
         << " (" << now->tm_hour  << ":"
         << now->tm_min  << ":"
         << now->tm_sec
         <<  ") "
         << std::setw(fileSize)
         << filename << ":"
         << line << " "
         << text
         <<  std::endl;
}

