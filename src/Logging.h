/*
 * Logging.h
 *
 *  Created on: Apr 7, 2019
 *      Author: user1
 */

#ifndef SRC_BSKLOGGING_H_
#define SRC_BSKLOGGING_H_

#include <stdio.h>
#include <sstream>

/**
 * Logging class.
 */
class Logging {
public:
   virtual ~Logging();

   static void logit(const char logType,
                     const std::string& file,
                     int line,
                     const std::string& text);

   static void timestamp(char* outTimestamp, int len);
private:
   Logging();

};

#define LOG( STREAM ) do {                               \
      std::stringstream LoggingString;                   \
      LoggingString << STREAM;              \
      Logging::logit('d', __FILE__, __LINE__, LoggingString.str() );  \
} while(0)

#define LOGD(FORMAT, ...) do { \
		char TIMESTAMP[20] = {0}; \
		Logging::timestamp(TIMESTAMP, 20); \
		printf ("D (%s:%d)[%s] " FORMAT "\n" , __FILE__, __LINE__, TIMESTAMP,  ##__VA_ARGS__ ); \
} while(0)

#define LOGI(FORMAT, ...) do { \
      char TIMESTAMP[20] = {0}; \
      Logging::timestamp(TIMESTAMP, 20); \
      printf ("I (%s:%d)[%s] " FORMAT "\n" , __FILE__, __LINE__, TIMESTAMP,  ##__VA_ARGS__ ); \
} while(0)

#define LOGW(FORMAT, ...) do { \
      char TIMESTAMP[20] = {0}; \
      Logging::timestamp(TIMESTAMP, 20); \
      printf ("W (%s:%d)[%s] " FORMAT "\n" , __FILE__, __LINE__, TIMESTAMP,  ##__VA_ARGS__ ); \
} while(0)

#define LOGE(FORMAT, ...) do { \
      char TIMESTAMP[20] = {0}; \
      Logging::timestamp(TIMESTAMP, 20); \
      printf ("E (%s:%d)[%s] " FORMAT "\n" , __FILE__, __LINE__, TIMESTAMP,  ##__VA_ARGS__ ); \
} while(0)

#endif /* SRC_BSKLOGGING_H_ */
