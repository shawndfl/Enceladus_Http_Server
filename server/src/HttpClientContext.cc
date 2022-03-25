
#include "HttpClientContext.h"
#include "Logging.h"
#include <unistd.h>
#include <string.h>

namespace ehs {
HttpClientContext::HttpClientContext(int clientfd, const std::string& ip) :
      request(ip), socketfd_(clientfd) {
   remoteIp_ = ip;
}

/*************************************************/
void HttpClientContext::sendResponse(bool autoClose) {

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

   sendRaw(out.c_str(), out.size());

   if(autoClose) {
      ::close(socketfd_);
   }
}

/*************************************************/
int HttpClientContext::getSocketfd() const {
   return socketfd_;
}

/*************************************************/
void HttpClientContext::sendRaw(const char *data, size_t size) {
   size_t bytesSent = write(socketfd_, data, size);
   if(bytesSent == (unsigned) -1) {
      LOGD("Error sending: " << strerror(errno));
   }
}

enum OptCode {
   OptContinue      = 0x00,
   OptText          = 0x01,
   OptBinary        = 0x02,
   OptReserved1     = 0x03,
   OptReserved2     = 0x04,
   OptReserved3     = 0x05,
   OptReserved4     = 0x06,
   OptReserved5     = 0x07,
   OptClose         = 0x08,
   OptPing          = 0x09,
   OptPong          = 0x0A,
   OptReserved6     = 0x0B,
   OptReserved7     = 0x0C,
   OptReserved8     = 0x0D,
   OptReserved9     = 0x0E,
   OptReserved10    = 0x0F,
};

struct WebSocketFrame {
   unsigned char  optcode        = 0;
   unsigned char  maskAndlength  = 0;
   unsigned int   extLength      = 0;
};

const unsigned short SmallFrame  = 16;
const unsigned short MidFrame    = 32;
const unsigned short LargeFrame  = 48;

/*************************************************/
void HttpClientContext::sendWebSocketFrame(const std::string &data) {

   WebSocketFrame frame;
   size_t size = data.size();

   size_t frameSize = SmallFrame;       // default is small frame
   int length;
   char lastFrame = 1;
   char noMask = 1;     // server does not send masked

   frame.optcode        = (lastFrame << 7) |  OptText;

   if(size > 0xffff) {
      length = 127;
      frameSize = LargeFrame;
   } else if(size > 125) {
      length = 126;
      frameSize = MidFrame;
   } else {
      length = size;
      frameSize = SmallFrame;
   }

   if(size > 0xFFFFFFFF){
      LOGD("Error packet too big it must be split into multiple frames");
   }

   frame.maskAndlength  = (noMask << 7)  |  (length & 0x7F);
   frame.extLength = size;

   sendRaw((const char*)&frame, frameSize);

   sendRaw(data.c_str(), data.size());
}

/*************************************************/
bool HttpClientContext::readRaw(std::string &data) {

   char buffer[1024] = { 0 };
   size_t bytesSent = 0;
   do {
      bytesSent = read(socketfd_, buffer, sizeof(buffer));

      if (bytesSent == (unsigned) -1) {
         if (errno != EAGAIN) {
            LOGD("Error sending: " << strerror(errno));
         } else {
            return false;
         }
         break;
      } else {
         data.append(buffer, buffer + sizeof(buffer));
      }
   } while (bytesSent != (size_t)-1);

   return true;
}

/*************************************************/
void HttpClientContext::readWebSocketFrame(const std::string &data) {
   //TODO implement web sockets
}

/*************************************************/
const std::string& HttpClientContext::getRemoteIp() const {
   return remoteIp_;
}

/*************************************************/
void HttpClientContext::close(const std::string &data) {
   ::close(socketfd_);
}
}

