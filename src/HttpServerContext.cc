
#include "HttpServerContext.h"

/*************************************************/
HttpServerContext::HttpServerContext(HttpServer &server):
   port_(0),
   socketfd_(-1),
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
void HttpServerContext::setPort(int port) {
   port_ = port;
}

/*************************************************/
void HttpServerContext::setSocketfd(int socketfd) {
   socketfd_ = socketfd;
}
/*************************************************/
