
#ifndef SRC_HTTPRESPONSE_H_
#define SRC_HTTPRESPONSE_H_

#include <string>
#include <vector>
#include "HttpConst.h"

namespace ehs {

/**
 * This structure can handle a response.
 * see https://tools.ietf.org/html/rfc7230#section-3.1.2
 * Format is:
 *    HTTP-version SP status-code SP reason-phrase CRLF
 *    Headers
 *    Message Body
 */
class HttpResponse {
public:

   enum StatusCode {
      CODE100,
      CODE101,
      CODE200,
      CODE201,
      CODE202,
      CODE203,
      CODE204,
      CODE205,
      CODE206,
      CODE300,
      CODE301,
      CODE302,
      CODE303,
      CODE304,
      CODE305,
      CODE307,
      CODE400,
      CODE401,
      CODE402,
      CODE403,
      CODE404,
      CODE405,
      CODE406,
      CODE407,
      CODE408,
      CODE409,
      CODE410,
      CODE411,
      CODE412,
      CODE413,
      CODE414,
      CODE415,
      CODE416,
      CODE417,
      CODE426,
      CODE500,
      CODE501,
      CODE502,
      CODE503,
      CODE504,
      CODE505,
   };

   HttpResponse();

   /**
    *  Status Line
    *  the http version
    */
   std::string httpVersion;

   /**
    * The 3 digit status code.
    * See https://tools.ietf.org/html/rfc7231#section-6
    *
    * 1xx (Informational): The request was received, continuing process
    * 2xx (Successful): The request was successfully received,
    *     understood, and accepted
    * 3xx (Redirection): Further action needs to be taken in order to
    *     complete the request
    * 4xx (Client Error): The request contains bad syntax or cannot be
    *     fulfilled
    * 5xx (Server Error): The server failed to fulfill an apparently
    *     valid request
    */
   StatusCode statusCode;

   /**
    * Gets the status code followed by the reason.
    */
   std::string getStatusCodeAndReason() const;

   /**
    * Fills in any headers that user did not fill in.
    */
   bool PrepareHeaders();

   /**
    * Headers
    */
   std::vector<Pair> headers;

   /**
    * appends a header line
    */
   void appendHeader(const std::string& key, const std::string& value);

   /**
    * Body
    */
   std::string body;

};

}
#endif /* SRC_HTTPRESPONSE_H_ */
