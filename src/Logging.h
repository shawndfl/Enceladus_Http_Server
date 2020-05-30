/*
 * Logging.h
 *
 *  Created on: Apr 7, 2019
 *      Author: user1
 */

#ifndef SRC_BSKLOGGING_H_
#define SRC_BSKLOGGING_H_

#include <stdio.h>

/**
 * Logging class.
 */
class Logging {
public:
   virtual ~Logging();
   static Logging* get();

   void logit(const char* logType, const char* file, int line, const char* text);
   void timestamp(char* outTimestamp, int len);
private:
   Logging();

};

#define LOGD(FORMAT, ...) do { \
		char TIMESTAMP[20] = {0}; \
		Logging::get()->timestamp(TIMESTAMP, 20); \
		printf ("D (%s:%d)[%s] " FORMAT "\n" , __FILE__, __LINE__, TIMESTAMP,  ##__VA_ARGS__ ); \
} while(0)

#define LOGI(FORMAT, ...) do { \
      char TIMESTAMP[20] = {0}; \
      Logging::get()->timestamp(TIMESTAMP, 20); \
      printf ("I (%s:%d)[%s] " FORMAT "\n" , __FILE__, __LINE__, TIMESTAMP,  ##__VA_ARGS__ ); \
} while(0)

#define LOGW(FORMAT, ...) do { \
      char TIMESTAMP[20] = {0}; \
      Logging::get()->timestamp(TIMESTAMP, 20); \
      printf ("W (%s:%d)[%s] " FORMAT "\n" , __FILE__, __LINE__, TIMESTAMP,  ##__VA_ARGS__ ); \
} while(0)

#define LOGE(FORMAT, ...) do { \
      char TIMESTAMP[20] = {0}; \
      Logging::get()->timestamp(TIMESTAMP, 20); \
      printf ("E (%s:%d)[%s] " FORMAT "\n" , __FILE__, __LINE__, TIMESTAMP,  ##__VA_ARGS__ ); \
} while(0)

#endif /* SRC_BSKLOGGING_H_ */
