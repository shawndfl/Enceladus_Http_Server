
#include "Logging.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

/*************************************************/
Logging::Logging() {
}

/*************************************************/
Logging::~Logging() {
}

/*************************************************/
Logging* Logging::get() {
   static Logging* instance = new Logging();
   return instance;
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
void Logging::logit(const char* logType, const char* file, int line,
      const char* text) {
   printf("%s %s(%d) %s\n", logType, file, line, text);
}

