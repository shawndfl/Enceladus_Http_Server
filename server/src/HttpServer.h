
#ifndef SRC_BSKHTTPSERVER_H_
#define SRC_BSKHTTPSERVER_H_

#include <queue>
#include <string>
#include <atomic>
#include <functional>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include "HttpClientContext.h"
#include "HttpServerContext.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpConst.h"

namespace ehs {

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
   bool StartServer(uint port, uint threadCount);

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
   void addRequestHandler(HttpRequestHandler handler);

   /**
    * Gets the user data for the request handler.
    */
   void* getUserData() const;

   /**
    * Joins with the accept thread
    */
   void JoinAcceptThread();


   void shutdown();

private:

   void acceptHandler();

   void requestHandler(const HttpServerContext& context);

private:

   typedef std::queue<std::shared_ptr<HttpClientContext> > RequestQueue;

   std::thread                      acceptThread_;
   std::vector<HttpRequestHandler>  filters_;
   HttpServerContext                serverContext_;

   RequestQueue                     requestQueue_;
   std::mutex                       requestMutex_;
   std::vector<std::thread>         requestThreads_;
   bool                             shutdown_;

   std::condition_variable          clientConnectCondition_;

};
}

#endif /* SRC_HttpServer_H_ */
