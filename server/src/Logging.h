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

namespace ehs {

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
}

#define LOGD(STREAM) do { \
      std::stringstream LoggingString;                   \
      LoggingString << STREAM;              \
      ehs::Logging::logit('d', __FILE__, __LINE__, LoggingString.str() );  \
} while(0)

#define LOGI(STREAM) do { \
      std::stringstream LoggingString;                   \
      LoggingString << STREAM;              \
      ehs::Logging::logit('i', __FILE__, __LINE__, LoggingString.str() );  \
} while(0)

#define LOGW(STREAM) do { \
      std::stringstream LoggingString;                   \
      LoggingString << STREAM;              \
      ehs::Logging::logit('w', __FILE__, __LINE__, LoggingString.str() );  \
} while(0)

#define LOGE(STREAM) do { \
      std::stringstream LoggingString;                   \
      LoggingString << STREAM;              \
      ehs::Logging::logit('e', __FILE__, __LINE__, LoggingString.str() );  \
} while(0)


#endif /* SRC_BSKLOGGING_H_ */
