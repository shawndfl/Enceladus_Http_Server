#ifndef SRC_HTTPCLIENTCONTEXT_H_
#define SRC_HTTPCLIENTCONTEXT_H_

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpConst.h"

namespace ehs {

/**
 * The context of the client connect.
 * The user should fill out the response structure
 * and call the SendResponse() function.
 */
class HttpClientContext {

public:
   HttpClientContext(int clientfd);

   /**
    * This will be filled in by the server.
    */
   HttpRequest  request;

   /**
    * The response from the server
    */
   struct HttpResponse response;

   /**
    * Call this after Response is fill out
    */
   void sendResponse(bool autoClose = true);

   /**
    * gets the client's socket
    */
   int getSocketfd() const;

   /**
    * Sends raw data for a web socket
    */
   void sendRaw(const char *data, size_t size);

   /**
    * Send a websocket frame
    */
   void sendWebSocketFrame(const std::string &data);


   /**
    * Send a websocket frame
    */
   void readWebSocketFrame(const std::string &data);


   /**
    * Sends raw data for a web socket
    */
   bool readRaw(std::string &data);

   /**
    * This is needed for websockets because the connection is left open
    */
   void close(const std::string& data);

private:
   int socketfd_;

};
}
#endif /* SRC_HTTPCLIENTCONTEXT_H_ */
