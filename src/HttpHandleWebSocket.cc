/*
 * HttpHandleWebSocket.cc
 *
 *  Created on: Feb 13, 2022
 *      Author: shawn
 */

#include "HttpHandleWebSocket.h"
#include "Logging.h"

HttpHandleWebSocket::HttpHandleWebSocket() {
   // TODO Auto-generated constructor stub

}

HttpHandleWebSocket::~HttpHandleWebSocket() {
   // TODO Auto-generated destructor stub
}

bool HttpHandleWebSocket::Handler(HttpClientContext &client, const HttpServerContext &server) {
   std::string upgrade = client.request.getHeader("Upgrade");
   if(upgrade == "websocket" ) {
      std::string key = client.request.getHeader("Sec-WebSocket-Key");
      LOG("Found web SOCKET!!");
      return true;
   } else {
      return false;
   }
}
