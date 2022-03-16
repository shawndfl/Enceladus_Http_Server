
#include "HttpResponse.h"
#include "Logging.h"

namespace ehs {

/*************************************************/
HttpResponse::HttpResponse() {
   statusCode = CODE500;
}

/*************************************************/
bool HttpResponse::PrepareHeaders() {

   return false;
}

/*************************************************/
void HttpResponse::appendHeader(const std::string& key, const std::string& value) {
   Pair pair;
   pair.first = key;
   pair.second = value;
   headers.push_back(pair);
}

/*************************************************/
std::string HttpResponse::getStatusCodeAndReason() const {

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
}
