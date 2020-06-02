
#include "HttpRequest.h"
#include "Logging.h"

/*************************************************/
HttpRequest::HttpRequest() :
      parseErrorCode(0), parsedState(HttpRequest::NewRequest) {

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
void HttpRequest::ParseRequest(const char* buffer, size_t size) {

   const char* ch = buffer;
   std::string token;
   size_t i = 0;

   while (parsedState != HttpRequest::Complete) {

      // there was an error some where
      if (parseErrorCode > 0)
         return;

      switch (parsedState) {

      case HttpRequest::IncompleteStartLine:
      case HttpRequest::NewRequest:
         // There is nothing to read
         // and the message is not complete
         if (i == size)
            return;

         // Parse Start Line
         for (i = 0; i < size; /* increment inside loop*/) {
            // End of line
            if (i + 1 < size && ch[i] == '\r' && ch[i + 1] == '\n') {
               ParseRequestLine(parsedLine);
               parsedState = HttpRequest::IncompleteHeader;
               parsedLine.clear(); // reset the parsed line
               i += 2; // Consume 2 chars
               break;
            } else {
               parsedState = HttpRequest::IncompleteStartLine;
               parsedLine += ch[i];
               i++; // Consume 1 char
            }
         }
         break;

      case HttpRequest::IncompleteHeader:
         // There is nothing to read
         // and the message is not complete
         if (i == size)
            return;

         // Headers
         for (/* Continue from last loop*/; i < size; /* increment inside loop*/) {
            // End of header
            if (i + 3 < size && ch[i] == '\r' && ch[i + 1] == '\n' && ch[i + 2] == '\r' && ch[i + 3] == '\n') {
               ParseHeaderLine(parsedLine);
               parsedState = HttpRequest::IncompleteMessage;
               parsedLine.clear(); // reset the parsed line
               i += 4; // Consume 4 chars
               break;
               // End of one header
            } else if (i + 1 < size && ch[i] == '\r' && ch[i + 1] == '\n') {
               ParseHeaderLine(parsedLine);
               parsedLine.clear(); // reset the parsed line
               i += 2; // Consume 2 chars
            } else {
               parsedState = HttpRequest::IncompleteHeader;
               if (ch[i] == '\0') {
                  LOGI("Found null at %zd", i);
               }
               parsedLine += ch[i];
               i++; // Consume 1 char
            }
         }

         break;
      case HttpRequest::IncompleteMessage:
         //TODO get the message length or chunk and parse it
         // Message
         for (; i < size; i++) {

         }

         parsedState = HttpRequest::Complete;

         break;
      default:
         LOGE("Unknown parse state: %d ", parsedState);
      }
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
