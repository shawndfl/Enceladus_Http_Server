
#ifndef SRC_BSKHTTPSERVER_H_
#define SRC_BSKHTTPSERVER_H_

#include <queue>
#include <pthread.h>
#include <string>
#include <atomic>
#include <functional>
#include <thread>
#include <mutex>
#include <vector>
#include "HttpClientContext.h"
#include "HttpServerContext.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpConst.h"

/**
 * The main server class used to start the server
 */
class HttpServer {
public:

   //TODO: add SSL

   HttpServer();
   virtual ~HttpServer();

   /**
    * Starts the server listening on the givne port.
    * This will spin up an accept thread. As clients connect
    * they will each get their own thread.
    */
   bool StartServer(int port);

   /**
    * Parses what we just got from the client.
    * This may not be a complete message.
    *
    * Returns - The function will return false if it detects an incomplete message
    */
   void ParseRequest(const char* buffer, size_t size, struct Request& outRequest);

   /**
    * Sets a user call back that handles the http request.
    * The handler will need to fill in the response structure then call
    * SendResponse().
    *
    * NOTE: The request handler is called on the client thread. Thread synchronization
    *       will be required when accessing shared resources.
    */
   void setRequestHandler(HttpRequestHandler handler);

   /**
    * User data that is passed to the handler.
    */
   void setUserData(void* userData);

   /**
    * Gets the user data for the request handler.
    */
   void* getUserData() const;

   /**
    * Joins with the accept thread
    */
   void JoinAcceptThread();

   /**
    * Gets the request handler
    */
   HttpRequestHandler getRequestHandler() const;

   void shutdown();

private:

   void acceptHandler();

   void requestHandler();

private:

   std::thread                acceptThread_;
   HttpRequestHandler         requestHandler_;
   HttpServerContext          serverContext_;

   bool                       shutdown_;
   std::mutex                 mutex_;
   std::vector<std::thread>   requestThreads_;

};

#endif /* SRC_HttpServer_H_ */
