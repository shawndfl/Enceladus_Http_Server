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

   /**
    * Handles the web socket request
    */
   virtual bool Handler(HttpClientContext& client, const HttpServerContext& server);

protected:

   /**
    * Initializes the web socket
    */
   virtual bool start(HttpClientContext& client, const HttpServerContext& server) = 0;

   /**
    * Call update
    */
   virtual bool update() = 0;

   virtual void close() = 0;
};

#endif /* SRC_HTTPHANDLEWEBSOCKET_H_ */
