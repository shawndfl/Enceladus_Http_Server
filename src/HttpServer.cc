
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

#include "Logging.h"

#include "HttpServer.h"

#define BACKLOG 50

bool readRequest(HttpClientContext& context);
size_t writen(int fd, const void* buffer, size_t size);

/*************************************************/
HttpServer::HttpServer() :
      serverContext_(*this) {
   shutdown_ = false;
}

/*************************************************/
HttpServer::~HttpServer() {
}

/*************************************************/
bool HttpServer::StartServer(int port) {

   if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
      LOGE( "Cannot filter SIGPIPE");
      return false;
   }

   // Creating socket file descriptor
   int fd;
   if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
      LOGE("socket error: %d", errno);
      return false;
   }
   serverContext_.setPort(port);
   serverContext_.setSocketfd(fd);

   // Forcefully attaching socket to the port 8080
   int opt = 1;
   if (setsockopt(serverContext_.getSocketfd(), SOL_SOCKET,
   SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
      LOGE("setsockopt error: %d", errno);
      return false;
   }

   if (setsockopt(serverContext_.getSocketfd(), SOL_SOCKET,
   SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
      LOGE("setsockopt error: %d", errno);
      return false;
   }

   struct sockaddr_in address;
   memset(&address, 0, sizeof(sockaddr_in));
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(serverContext_.getPort());

   // socket to the port
   if (bind(serverContext_.getSocketfd(), (struct sockaddr *) &address, sizeof(address)) < 0) {
      LOGE("Error binding to port %d", serverContext_.getPort());
      return false;
   }

   if (listen(serverContext_.getSocketfd(), BACKLOG) < 0) {
      LOGE("Error listen %d %d",serverContext_.getSocketfd(), errno);
      return false;
   }

   LOGI("Listening on port %d", serverContext_.getPort());

   std::thread accept(&HttpServer::acceptHandler, this);
   acceptThread_  = std::move(accept);

   return true;
}

/*************************************************/
void HttpServer::shutdown() {
   std::lock_guard<std::mutex> lock(mutex_);
   shutdown_ = true;
}

/*************************************************/
void HttpServer::JoinAcceptThread() {

   if(acceptThread_.joinable()){
      acceptThread_.join();
   }

   LOGI("Join main thread ");
}

/*************************************************/
void HttpServer::addRequestHandler(HttpRequestHandler handler) {
   filters_.push_back(handler);
}

/*************************************************/
void HttpServer::acceptHandler() {


   while (true) {

      struct sockaddr clientAddr;
      socklen_t addrLen = sizeof(clientAddr);
      int clientfd = accept(serverContext_.getSocketfd(), &clientAddr, &addrLen);
      if (clientfd < 0) {
         LOGE("Error accept %d %d", clientfd, errno);
         break;
      }

      {
         // see if we should exit this loop
         std::lock_guard<std::mutex> lock(mutex_);
         if (shutdown_) {
            break;
         }
      }

      //TODO add ip address of client
      LOGI("Got a client %d", clientfd);

      HttpClientContext context(clientfd);
      std::thread clientThread(&HttpServer::requestHandler, this, context);
      requestThreads_.push_back(std::move(clientThread));
   }

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

bool readRequest(HttpClientContext& context) {

   const size_t size = 4096;
   char buffer[size] = { 0 };
   std::vector<std::string> lines;
   bool headerDone = false;
   std::string line;

   while (true) {

      size_t bytesRead = read(context.getSocketfd(), buffer, size);
      if (bytesRead == (size_t)-1) {

         // Interrupted restart
         if (errno == EINTR) {
            continue;
         } else {
            LOGE("Error reading %d ", errno);
            return false;
         }
      }

      // loop over each byte
      for(size_t i = 0; i < bytesRead; i++) {

         if(!headerDone) {
            // see if we found a new line
            if(i < bytesRead -1 &&  buffer[i] == '\r' && buffer[i+1] =='\n') {

               line += buffer[i  ];    // save the '\r'
               line += buffer[++i];    // save the '\n'

               // done with headers but may have a message body
               if (line == "\r\n") {
                  headerDone = true;
               }
               lines.push_back(line);  // save the line

               line = "";

            } else {
               line += buffer[i];
            }

         // collect the body
         } else {
            line += buffer[i];
         }
      }

      // parse the header we will still need the body
      if(headerDone) {
         context.request.parseLines(lines);
         break;
      }

   }

   return true;
}

/*************************************************/
void HttpServer::requestHandler(HttpClientContext context) {

   LOGI("Got a client");

   while (true) {

      // Read the request
      if (!readRequest(context)) {
         LOGE("Error reading request from %d:", context.getSocketfd());
         break;
      }

      // Set the http version
      context.response.httpVersion = HTTP_VERSION;

      // Fill in the date header
      char buf[200];
      time_t now = time(0);
      struct tm tm = *gmtime(&now);

      // Sun, 06 Nov 1994 08:49:37 GMT
      strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
      context.response.appendHeader("Date", std::string(buf));

      // Fill in the server Header
      context.response.appendHeader("Server", "Embedded");

      // Let the user handle the request
     for(auto filter: filters_) {
        if(filter(context, serverContext_)) {
           break;
        }
     }

      break;
   }
}
