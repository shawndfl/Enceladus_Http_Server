#ifndef SRC_HTTPREQUEST_H_
#define SRC_HTTPREQUEST_H_

#include <string>
#include <vector>
#include "HttpConst.h"

/**
 * The request from the client.
 *  See https://tools.ietf.org/html/rfc7230#section-3.1.1
 *  Format is:
 *    method SP request-target SP HTTP-version CRLF
 *    Headers
 *       key: value
 *    Body
 */
class HttpRequest {
public:
   enum ParseState {
      NewRequest, IncompleteStartLine, IncompleteHeader, IncompleteMessage, Complete, ParseError
   };

   HttpRequest();

   /**
    * gets the size of the body based on the
    */
   int getBodySize() const;

   /**
    * Starts the request parsing process. This function will call
    * ParseRequestLine(), ParseHeaderLine(), and AppendToBody()
    */
   void ParseRequest(const char* buffer, size_t size);
   void parseLines(std::vector<std::string>& lines);

   const std::string& getBody() const;
   const std::vector<Pair>& getHeaders() const;
   const std::string& getHttpVersion() const;
   const std::string& getMethod() const;
   const std::string& getParsedLine() const;
   ParseState getParsedState() const;
   int getParseErrorCode() const;
   const std::string& getUri() const;
   const std::vector<Pair>& getQueryParameters() const;
   const std::string& getUriPath() const;
   const std::string& getUriQuery() const;

   std::string getHeader(const std::string& header) const;

private:
   /**
    * Parses the request line. This is the first line in
    * the request. Its format is:
    *    method SP request-target SP HTTP-version CRLF
    *
    * NOTE: Don't call directory ParseRequest()
    * calls this.
    */
   bool ParseRequestLine(const std::string& line);
   /**
    * Parse header. This will parse a single line.
    * it should be in the form of:
    *    field-name: field-value
    *
    * NOTE: Don't call directory ParseRequest()
    * calls this.
    */
   bool ParseHeaderLine(const std::string& line);

   /**
    * This will append a chunk to the message
    * body.
    *
    * NOTE: Don't call directory ParseRequest()
    * calls this.
    */
   bool AppendToBody(const std::string& chunk);

   /**
    * This error code can be set when parsing
    * the request. If invalid characters are found
    * this will be set and a response will be sent
    * to the client with this number.
    */
   int parseErrorCode;

   /**
    * The state of the request. It may be incomplete
    * due to tcp frames
    */
   ParseState parsedState;

   /**
    * The line that is being read from
    * the network. When The message is
    * complete this will be empty. Else
    * it will be the last line in the buffer.
    *
    * The next read will append to this and continue
    * parsing.
    */
   std::string parsedLine;

   /**
    *  The http version
    */
   std::string httpVersion;

   /**
    * The request method
    * See https://tools.ietf.org/html/rfc7231#section-4
    *     +---------+-------------------------------------------------+-------+
    *     | Method  | Description                                     | Sec.  |
    *     +---------+-------------------------------------------------+-------+
    *     | GET     | Transfer a current representation of the target | 4.3.1 |
    *     |         | resource.                                       |       |
    *     | HEAD    | Same as GET, but only transfer the status line  | 4.3.2 |
    *     |         | and header section.                             |       |
    *     | POST    | Perform resource-specific processing on the     | 4.3.3 |
    *     |         | request payload.                                |       |
    *     | PUT     | Replace all current representations of the      | 4.3.4 |
    *     |         | target resource with the request payload.       |       |
    *     | DELETE  | Remove all current representations of the       | 4.3.5 |
    *     |         | target resource.                                |       |
    *     | CONNECT | Establish a tunnel to the server identified by  | 4.3.6 |
    *     |         | the target resource.                            |       |
    *     | OPTIONS | Describe the communication options for the      | 4.3.7 |
    *     |         | target resource.                                |       |
    *     | TRACE   | Perform a message loop-back test along the path | 4.3.8 |
    *     |         | to the target resource.                         |       |
    *     +---------+-------------------------------------------------+-------+
    */
   std::string method;

   /**
    * The request target. This is the url and the query
    */
   std::string uri;

   /**
    * The path part of the uri. This will not have the query (any thing after the '?')
    * This path is always lower case
    */
   std::string uriPath;

   /**
    * The query portion of the uri. (any thing after the '?'). This will also get split up into
    * parameters that can be found in queryParameters.
    */
   std::string uriQuery;

   /**
    * Parameters used by the request. This is pulled out
    * of the Uri query.
    */
   std::vector<Pair> queryParameters;

   /**
    * Headers
    */
   std::vector<Pair> headers;

   /**
    * Body
    */
   std::string body;

};

#endif /* SRC_HTTPREQUEST_H_ */
