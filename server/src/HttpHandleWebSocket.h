/*
 * HttpHandleWebSocket.h
 *
 *  Created on: Feb 13, 2022
 *      Author: shawn
 */

#ifndef SRC_HTTPHANDLEWEBSOCKET_H_
#define SRC_HTTPHANDLEWEBSOCKET_H_

#include "HttpClientContext.h"
#include "HttpServerContext.h"

/**
 * This class will handle a web socket connection
 */
class HttpHandleWebSocket {
public:
   HttpHandleWebSocket();
   virtual ~HttpHandleWebSocket();

   bool Handler(HttpClientContext& client, const HttpServerContext& server);
};

#endif /* SRC_HTTPHANDLEWEBSOCKET_H_ */
