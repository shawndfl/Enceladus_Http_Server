
#include "HttpClientContext.h"
#include "Logging.h"
#include <unistd.h>

HttpClientContext::HttpClientContext(int clientfd) :
      socketfd_(clientfd) {

}

/*************************************************/
void HttpClientContext::SendResponse() {

   std::string out;
   out = response.httpVersion + " " + response.getStatusCodeAndReason() + "\r\n";

   // Fill in the size of the content
   char buf[200] = { 0 };
   size_t size = response.body.size();
   sprintf(buf, "%zd", size);
   response.appendHeader("Content-Length", buf);

   // Write the headers
   for (size_t i = 0; i < response.headers.size(); i++) {
      Pair pair = response.headers.at(i);
      out += pair.first + ": " + pair.second + "\r\n";
   }

   // Done with headers
   out += "\r\n";

   // Write the body
   out += response.body;
   size_t bytesSent = write(socketfd_, out.c_str(), out.size());
   if (bytesSent < 0) {
      //EROFS
      LOGE("Error sending %d ", errno);
   }

   close(socketfd_);
}

/*************************************************/
int HttpClientContext::getSocketfd() const {
   return socketfd_;
}
