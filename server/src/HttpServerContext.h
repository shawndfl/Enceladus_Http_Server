
#ifndef SRC_HTTPSERVERCONTEXT_H_
#define SRC_HTTPSERVERCONTEXT_H_

#include "HttpServerContext.h"
#include "HttpClientContext.h"

class HttpServer;

/**
 * The structure for the server connection
 */
class HttpServerContext {
public:

   HttpServerContext(HttpServer& server);

   int getPort() const;

   const HttpServer& getServer() const;

   int getSocketfd() const;

   void setPort(int port);

   void setSocketfd(int socketfd);

   bool HandleRequest(HttpClientContext& client, const HttpServerContext& server);

private:

   int         port_;
   int         socketfd_;
   HttpServer& server_;

};

#endif /* SRC_HTTPSERVERCONTEXT_H_ */
