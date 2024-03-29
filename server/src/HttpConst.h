
#ifndef SRC_HTTPCONST_H_
#define SRC_HTTPCONST_H_

#include <functional>

namespace ehs {

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
typedef std::function<bool(HttpClientContext&, const HttpServerContext&)> HttpRequestHandler;

}
#endif /* SRC_HTTPCONST_H_ */
