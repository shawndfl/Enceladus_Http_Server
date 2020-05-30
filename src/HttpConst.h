
#ifndef SRC_HTTPCONST_H_
#define SRC_HTTPCONST_H_

#include <functional>

class HttpClientContext;
class HttpServerContext;

#define HTTP_VERSION "HTTP/1.1"

typedef std::function<void(HttpClientContext&, const HttpServerContext&)> RequestHandler;



#endif /* SRC_HTTPCONST_H_ */
