
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>

#include "Logging.h"

#include "HttpServer.h"

#define BACKLOG 50

void* acceptEvent(void * context);
void* readEvent(void * context);
size_t readn(int fd, HttpRequest& request);
size_t writen(int fd, const void* buffer, size_t size);

/*************************************************/
HttpServer::HttpServer() {

}

/*************************************************/
HttpServer::~HttpServer() {
}

/*************************************************/
bool HttpServer::StartServer(int port) {

   if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
      LOGE("Cannot filter SIGPIPE");
      return false;
   }


   // Creating socket file descriptor
   int fd;
   if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
      LOGE("socket error: %d", errno);
      return false;
   }
   HttpServerContext context(port, fd, *this);

   // Forcefully attaching socket to the port 8080
   int opt = 1;
   if (setsockopt(context.getSocketfd(), SOL_SOCKET,
   SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
      LOGE("setsockopt error: %d", errno);
      return false;
   }

   if (setsockopt(context.getSocketfd(), SOL_SOCKET,
   SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
      LOGE("setsockopt error: %d", errno);
      return false;
   }

   struct sockaddr_in address;
   //memset(&address, 0, sizeof(sockaddr_in));
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(context.getPort());

   // socket to the port
   if (bind(context.getSocketfd(), (struct sockaddr *) &address, sizeof(address)) < 0) {
      LOGE("Error binding to port %d", context.getPort());
      return false;
   }

   if (listen(context.getSocketfd(), BACKLOG) < 0) {
      LOGE("Error listen %d %d",context.getSocketfd(), errno);
      return false;
   }

   LOGI("Listening on port %d", context.getPort());

   pthread_attr_t attr;
   pthread_attr_init(&attr);
   pthread_create(&_acceptThread, &attr, &acceptEvent, &serverContext_);
   pthread_attr_destroy(&attr);

   return true;
}

/*************************************************/
void HttpServer::JoinAcceptThread() {
   int ret;
   int* retp = &ret;

   pthread_join(_acceptThread, (void**) &retp);

   LOGI("Join main thread %d", ret);
}

/*************************************************/
RequestHandler HttpServer::getRequestHandler() const {
   return _requestHandler;
}

/*************************************************/
void HttpServer::setRequestHandler(RequestHandler handler) {
   _requestHandler = handler;
}

/*************************************************/
void* HttpServer::getUserData() const {
   return _userData;
}

/*************************************************/
void HttpServer::setUserData(void* userData) {
   _userData = userData;
}

/*************************************************/
// Client Context
/*************************************************/
void ClientContext::SendResponse() {

   std::string out;
   out = response.httpVersion + " " + response.getStatusCodeAndReason() + "\r\n";

   // Fill in the size of the content
   char buf[200] = { 0 };
   size_t size = response.body.size();
   sprintf(buf, "%zd", size);
   response.appendHeader("Content-Length", buf);

   // Write the headers
   for (size_t i = 0; i < response.headers.size(); i++) {
      KeyValue pair = response.headers.at(i);
      out += pair.key + ": " + pair.value + "\r\n";
   }

   // Done with headers
   out += "\r\n";

   // Write the body
   out += response.body;

   size_t bytesSent = writen(clientfd, out.c_str(), out.size());
   if (bytesSent < 0) {
      //EROFS
      LOGE("Error sending %d ", errno);
   }

   // TODO don't close this here. check to keep alive
   close(clientfd);

}

/*************************************************/
// Response
/*************************************************/
bool Response::PrepareHeaders() {

   return false;
}

/*************************************************/
void Response::appendHeader(const std::string& key, const std::string& value) {
   KeyValue pair;
   pair.key = key;
   pair.value = value;
   headers.push_back(pair);
}

/*************************************************/
std::string Response::getStatusCodeAndReason() const {

   switch (statusCode) {
   case CODE100:
      return "100 Continue";
   case CODE101:
      return "101 Switching Protocols";
   case CODE200:
      return "200 OK";
   case CODE201:
      return "201 Created";
   case CODE202:
      return "202 Accepted";
   case CODE203:
      return "203 Non-Authoritative Information";
   case CODE204:
      return "204 No Content";
   case CODE205:
      return "205 Reset Content";
   case CODE206:
      return "206 Partial Content";
   case CODE300:
      return "300 Multiple Choices";
   case CODE301:
      return "301 Moved Permanently";
   case CODE302:
      return "302 Found";
   case CODE303:
      return "303 See Other";
   case CODE304:
      return "304 Not Modified";
   case CODE305:
      return "305 Use Proxy";
   case CODE307:
      return "307 Temporary Redirect";
   case CODE400:
      return "400 Bad Request";
   case CODE401:
      return "401 Unauthorized";
   case CODE402:
      return "402 Payment Required";
   case CODE403:
      return "403 Forbidden";
   case CODE404:
      return "404 Not Found";
   case CODE405:
      return "405 Method Not Allowed";
   case CODE406:
      return "406 Not Acceptable";
   case CODE407:
      return "407 Proxy Authentication Required";
   case CODE408:
      return "408 Request Timeout";
   case CODE409:
      return "409 Conflict";
   case CODE410:
      return "410 Gone";
   case CODE411:
      return "411 Length Required";
   case CODE412:
      return "412 Precondition Failed";
   case CODE413:
      return "413 Payload Too Large";
   case CODE414:
      return "414 URI Too Long";
   case CODE415:
      return "415 Unsupported Media Type";
   case CODE416:
      return "416 Range Not Satisfiable";
   case CODE417:
      return "417 Expectation Failed";
   case CODE426:
      return "426 Upgrade Required";
   case CODE500:
      return "500 Internal Server Error";
   case CODE501:
      return "501 Not Implemented";
   case CODE502:
      return "502 Bad Gateway";
   case CODE503:
      return "503 Service Unavailable";
   case CODE504:
      return "504 Gateway Timeout";
   case CODE505:
      return "505 HTTP Version Not Supported";
   default:
      LOGE("Unknown return code: %d ", statusCode);
      return "500 Internal Server Error";
   }
}

/*************************************************/
// Request


/*************************************************/
// Helper functions
/*************************************************/
void* acceptEvent(void * context) {

   ServerContext* serverContext = (ServerContext*) context;

   while (true) {

      struct sockaddr clientAddr;
      socklen_t addrLen = sizeof(clientAddr);
      int clientfd = accept(serverContext->serverfd, &clientAddr, &addrLen);
      if (clientfd < 0) {
         LOGE("Error accept %d %d", clientfd, errno);
         exit(EXIT_FAILURE);
      }

      //TODO add ip address of client
      LOGI("Got a client %d", clientfd);

      ClientContext* receiveContext = new ClientContext(serverContext->server, clientfd);

      pthread_attr_t attr;
      pthread_attr_init(&attr);
      pthread_create(&receiveContext->thread, &attr, &readEvent, receiveContext);
      pthread_attr_destroy(&attr);
   }

   return nullptr;
}

/*************************************************/
size_t readn(int fd, Request& request) {

   size_t totalBytesRead = 0;

   // There is a chance that our buffer is too small for the
   // request. This look will allow us to keep reading until we
   // get a complete request or an error.
   while (request.getParsedState() != Request::Complete) {

      // Handle parse errors
      if (request.getParseErrorCode() > 0) {
         return -1;
      }

      const size_t size = 4096;
      char buffer[size] = { 0 };
      char* chBufer = buffer;
      volatile size_t bufferBytesRead = 0;
      volatile size_t bytesRead = 0;
      while (bufferBytesRead < size) {

         bytesRead = read(fd, chBufer, size - bufferBytesRead);
         if (bytesRead == (size_t) -1) {

            // Interrupted restart
            if (errno == EINTR) {
               continue;
            } else {
               LOGE("Error reading %d ", errno);
               return -1;
            }
         }

         // EOF
         if (bytesRead == 0) {
            return bufferBytesRead;
         }

         // Parse the request
         request.ParseRequest(chBufer, bytesRead);

         // All done. Got the full request.
         if (request.getParsedState() == Request::Complete) {
            break;
         }
         bufferBytesRead += bytesRead;
         chBufer += bytesRead;
         totalBytesRead += bytesRead;
      }
   }
   return totalBytesRead;
}

/*************************************************/
size_t writen(int fd, const void* buffer, size_t size) {
   char* chBuffer = (char*) buffer;
   size_t totalBytesWrote = 0;
   size_t bytesWrote = 0;
   while (totalBytesWrote < size) {

      bytesWrote = write(fd, chBuffer, size - totalBytesWrote);

      // EOF
      if (bytesWrote <= 0) {
         // Interrupted restart
         if (bytesWrote == (size_t) -1 && errno == EINTR) {
            continue;
         } else {
            LOGE("Error writing %d ", errno);
            return -1;
         }
      }
      totalBytesWrote += bytesWrote;
      chBuffer += bytesWrote;
   }
   return totalBytesWrote;
}

/*************************************************/
void* readEvent(void * context) {
   ClientContext* clientContext = (ClientContext*) context;

   LOGI("Got a client %d", clientContext->clientfd);

   while (true) {

      // Read the request
      int bytesRead = readn(clientContext->clientfd, clientContext->request);
      if (bytesRead == -1) {
         LOGE("Error reading request from %d", clientContext->clientfd);
         break;
      }

      // TODO move this to a initialize response function
      // Set the http version
      clientContext->response.httpVersion = HTTP_VERSION;

      // Fillin the date header
      char buf[200];
      time_t now = time(0);
      struct tm tm = *gmtime(&now);
      // Sun, 06 Nov 1994 08:49:37 GMT
      strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
      clientContext->response.appendHeader("Date", std::string(buf));

      // Fill in the server Header
      clientContext->response.appendHeader("Server", "Embedded");

      // Let the user handle the request
      if (clientContext->server->getRequestHandler() != nullptr) {
         clientContext->server->getRequestHandler()(clientContext, clientContext->server->getUserData());
      } else {
         LOGW("No request handler. Call HttpServer::setRequestHandler()");
      }

      break;
   }
   return nullptr;
}
