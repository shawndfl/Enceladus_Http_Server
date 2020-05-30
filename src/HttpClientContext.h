#ifndef SRC_HTTPCLIENTCONTEXT_H_
#define SRC_HTTPCLIENTCONTEXT_H_

#include "HttpRequest.h"
#include "HttpResponse.h"

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
   struct HttpRequest request;

   /**
    * The response from the server
    */
   struct HttpResponse response;

   /**
    * Call this after Response is fill out
    */
   void SendResponse();
private:
   int clientfd_;

};

#endif /* SRC_HTTPCLIENTCONTEXT_H_ */
