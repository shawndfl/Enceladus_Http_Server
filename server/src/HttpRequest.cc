
#include "HttpRequest.h"
#include "Logging.h"
#include <locale>         // std::locale, std::tolower
#include <algorithm>

namespace ehs {

/*************************************************/
HttpRequest::HttpRequest() :
      parseErrorCode(0), parsedState(HttpRequest::NewRequest) {

}

/*************************************************/
std::string HttpRequest::getHeader(const std::string& header) const {
   for(int i =0; i < headers.size(); i++) {
      if(headers[i].first == header) {
         return headers[i].second;
      }
   }
   return "";
}

/*************************************************/
bool HttpRequest::ParseRequestLine(const std::string& line) {
   size_t i = 0;

   // Find method
   for (i = 0; i < line.size(); i++) {
      char ch = line.at(i);
      // done with method
      if (ch == ' ') {
         i++;
         break;
      }
      method += ch;
   }

   // Find uri
   for (/*continue from last loop*/; i < line.size(); i++) {
      char ch = line.at(i);

      // done with uri
      if (ch == ' ') {
         i++;

         break;
      }
      uri += ch;
   }

   // Find httpVersion
   for (/*continue from last loop*/; i < line.size(); i++) {
      char ch = line.at(i);
      // done with httpVersion. This char should not be here but
      // just in case
      if (ch == '\r') {
         i++;
         break;
      }
      httpVersion += ch;
   }

   // parse the uri to find the uri path
   for (i = 0; i < uri.size(); i++) {
      char ch = uri.at(i);

      // found a query
      if (ch == '?') {
         i++;
         break;
      }
      uriPath += ch;
   }

   std::locale loc;
   std::transform(uriPath.begin(), uriPath.end(), uriPath.begin(),
       [](unsigned char c){ return std::tolower(c); });

   const int KEY = 0;
   const int VALUE = 1;
   int state = KEY;

   std::string key;
   std::string value;

   // parse the uri to find the uri path
   for (/*continue from last loop*/; i < uri.size(); i++) {
      char ch = uri.at(i);

      // found a query
      if (ch == '#') {
         i++;
         break;
      }

      // collect the key
      if (state == KEY && ch != '=') {
         key += ch;
         // start collecting the value next iteration
      } else if (state == KEY && ch == '=') {
         state = VALUE;
         //collect value
      } else if (state == VALUE && ch != '&') {
         // replace + with space
         if (ch == '+') {
            value += ' ';
            // process hex values
         } else if (ch == '%') {
            if (i + 2 < uri.size()) {
               char hex[] = { uri.at(++i), uri.at(++i), '\0' };
               unsigned char hexChar = (unsigned char) strtol(hex, NULL, 16);

               if (hexChar < 0x1F || hexChar > 0x7E) {
                  LOGE("Hex value out of range: value=%d Range is 32 to 126", (unsigned char)hexChar);
               } else {
                  value += hexChar;
               }
            } else {
               LOGE("Expected hex value ");
            }

         } else {
            value += ch;
         }
         // got a key and a value. Save it and collect next key
      } else if (state == VALUE && ch == '&') {
         state = KEY;

         Pair pair;
         pair.first = key;
         pair.second = value;
         queryParameters.push_back(pair);
         key.clear();
         value.clear();
      }

      uriQuery += ch;
   }

   // Save the last one
   if (key.size() > 0 && value.size() > 0) {
      Pair pair;
      pair.first = key;
      pair.second = value;
      queryParameters.push_back(pair);
   }

   return true;
}

/*************************************************/
bool HttpRequest::ParseHeaderLine(const std::string& line) {
   size_t i = 0;
   Pair pair;

   // Find field name
   for (i = 0; i < line.size(); i++) {
      char ch = line.at(i);
      // done with key
      if (ch == ':') {
         i++;
         break;
      }
      pair.first += ch;
   }

   // Trim white space
   for (/*continue from last loop*/; i < line.size(); i++) {
      char ch = line.at(i);
      if (ch != ' ') {
         break;
      }
   }

   // Find field value
   for (/*continue from last loop*/; i < line.size(); i++) {
      char ch = line.at(i);
      // done with httpVersion. This char should not be here but
      // just in case
      if (ch == '\r') {
         i++;
         break;
      }
      pair.second += ch;
   }

   headers.push_back(pair);

   return true;
}

/*************************************************/
bool HttpRequest::AppendToBody(const std::string& chunk) {
   return true;
}

/*************************************************/
void HttpRequest::parseLines(std::vector<std::string>& lines) {
   method = "";
   httpVersion = "";
   uri = "";
   uriPath ="";
   uriQuery = "";
   queryParameters.clear();
   headers.clear();
   body = "";


   bool requestLine = true;
   for(auto line: lines) {
      if(requestLine) {
         ParseRequestLine(line);
         requestLine = false;
      } else {
         ParseHeaderLine(line);
      }
      LOG(line.substr(0, line.size()-2));
   }
}

/*************************************************/
const std::vector<Pair>& HttpRequest::getQueryParameters() const {
   return queryParameters;
}

/*************************************************/
const std::string& HttpRequest::getUriPath() const {
   return uriPath;
}

/*************************************************/
const std::string& HttpRequest::getUriQuery() const {
   return uriQuery;
}

/*************************************************/
const std::string& HttpRequest::getBody() const {
   return body;
}

/*************************************************/
const std::vector<Pair>& HttpRequest::getHeaders() const {
   return headers;
}

/*************************************************/
const std::string& HttpRequest::getHttpVersion() const {
   return httpVersion;
}

/*************************************************/
const std::string& HttpRequest::getMethod() const {
   return method;
}

/*************************************************/
const std::string& HttpRequest::getParsedLine() const {
   return parsedLine;
}

/*************************************************/
HttpRequest::ParseState HttpRequest::getParsedState() const {
   return parsedState;
}

/*************************************************/
int HttpRequest::getParseErrorCode() const {
   return parseErrorCode;
}

/*************************************************/
const std::string& HttpRequest::getUri() const {
   return uri;
}
}
