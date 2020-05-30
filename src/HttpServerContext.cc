
#include "HttpServerContext.h"

/*************************************************/
HttpServerContext::HttpServerContext(int port, int socketfd, HttpServer &server):
   port_(port),
   socketfd_(socketfd),
   server_(server)  {

}

/*************************************************/
int HttpServerContext::getPort() const {
   return port_;
}

/*************************************************/
const HttpServer&& HttpServerContext::getServer() const {
   return server_;
}

/*************************************************/
int HttpServerContext::getSocketfd() const {
   return socketfd_;
}
/*************************************************/
