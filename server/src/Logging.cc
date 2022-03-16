
#include "Logging.h"

#include <chrono>
#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace ehs {

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

   struct timeval curTime;
   gettimeofday(&curTime, NULL);
   struct tm* time =localtime(&curTime.tv_sec);

   const int fileSize = 20;
   std::string filename;
   if(file.size() > fileSize - 3) {
      filename = "..." + file.substr(file.size() - (fileSize -3) );
   } else {
      filename = file;
   }

   std::cout << logType
         << " (" << time->tm_hour  << ":"
         << time->tm_min  << ":"
         << time->tm_sec << "."
			<< std::fixed
			<<  std::setw(6)
			<< std::setfill('0') << curTime.tv_usec
         <<  ") "
			<< std::setfill(' ')
         << std::setw(fileSize)
         << filename << ":"
         << line << " "
         << text
         <<  std::endl;
}
}
