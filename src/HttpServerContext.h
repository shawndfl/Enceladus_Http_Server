
#ifndef SRC_HTTPSERVERCONTEXT_H_
#define SRC_HTTPSERVERCONTEXT_H_

class HttpServer;

/**
 * The structure for the server connection
 */
class HttpServerContext {
public:

   HttpServerContext(HttpServer& server);

   int getPort() const;

   const HttpServer&& getServer() const;

   int getSocketfd() const;

   void setPort(int port);

   void setSocketfd(int socketfd);

private:

   int         port_;
   int         socketfd_;
   HttpServer& server_;

};

#endif /* SRC_HTTPSERVERCONTEXT_H_ */
