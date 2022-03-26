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
#include "IRequestHandler.h"

namespace ehs {
/**
 * Handles any http request for a file
 */
class HttpHandleFile: public IRequestHandler {
public:
   HttpHandleFile(const std::string& contentPath);
   virtual ~HttpHandleFile();

   /**
    * Handles the request for a file.
    */
   virtual bool Handler(HttpClientContext& client, const HttpServerContext& server);

private:
   std::string  contentPath_;
};
}
#endif /* SRC_HTTPHANDLEFILE_H_ */
