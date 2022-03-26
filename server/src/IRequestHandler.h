/*
 * IRequestHandler.h
 *
 *  Created on: Mar 25, 2022
 *      Author: shawn
 */

#ifndef SERVER_SRC_IREQUESTHANDLER_H_
#define SERVER_SRC_IREQUESTHANDLER_H_

#include "HttpClientContext.h"
#include "HttpServerContext.h"

namespace ehs {

class IRequestHandler {
public:
   virtual ~IRequestHandler();

   virtual bool handler(HttpClientContext& client, const HttpServerContext& server);

   virtual bool onOpen(HttpClientContext& client, const HttpServerContext& server);

   virtual bool onMessage(HttpClientContext& client, const HttpServerContext& server);

   virtual bool onClose(HttpClientContext& client, const HttpServerContext& server);

protected:
   IRequestHandler();
};

} /* namespace ehs */

#endif /* SERVER_SRC_IREQUESTHANDLER_H_ */
