/*
 * Json.h
 *
 *  Created on: May 31, 2020
 *      Author: sdady
 */

#ifndef SRC_JSON_H_
#define SRC_JSON_H_
#include <string>


class Json {
public:
   Json();
   virtual ~Json();

   void parse(const std::string& json);

};

#endif /* SRC_JSON_H_ */
