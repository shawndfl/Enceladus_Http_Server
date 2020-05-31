
#ifndef SRC_HTTPCONST_H_
#define SRC_HTTPCONST_H_

#include <functional>

class HttpClientContext;
class HttpServerContext;

#define HTTP_VERSION "HTTP/1.1"

/**
 * Key value type
 */
typedef std::pair<std::string,std::string> Pair;

/**
 * Request handler callback
 */
typedef std::function<void(HttpClientContext&, const HttpServerContext&)> HttpRequestHandler;



#endif /* SRC_HTTPCONST_H_ */
