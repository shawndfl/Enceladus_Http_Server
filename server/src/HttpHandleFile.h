/*
 * HttpHandleFile.h
 *
 *  Created on: Jun 6, 2020
 *      Author: sdady
 */

#ifndef SRC_HTTPHANDLEFILE_H_
#define SRC_HTTPHANDLEFILE_H_

#include "HttpClientContext.h"
#include "HttpServerContext.h"

namespace ehs {
class HttpHandleFile {
public:
   HttpHandleFile();
   virtual ~HttpHandleFile();

   bool Handler(HttpClientContext& client, const HttpServerContext& server);
};
}
#endif /* SRC_HTTPHANDLEFILE_H_ */
