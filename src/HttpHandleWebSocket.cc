/*
 * HttpHandleWebSocket.cc
 *
 *  Created on: Feb 13, 2022
 *      Author: shawn
 */

#include "HttpHandleWebSocket.h"
#include "Logging.h"
#include "Base64.h"
#include "sha1.h"
#include <thread>

const char* WebSocketGUID="258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

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

      //
      std::string socketKey = key + WebSocketGUID;
      SHA1 sha1;
      sha1.Input(socketKey.c_str(), socketKey.size());

      unsigned dig[5];
      sha1.Result(dig);
      std::string encoding = Base64::encode((char*)&dig[0], sizeof(dig));

      client.response.appendHeader("Sec-WebSocket-Accept", encoding);
      client.response.appendHeader("Connection", "Upgrade" );
      client.response.appendHeader("upgrade", "websocket");
      client.response.appendHeader("Sec-WebSocket-Extensions", "permessage-deflate; client_no_context_takeover" );
      client.response.statusCode = HttpResponse::CODE101;

      client.sendResponse(false);

      std::string response;

      for (int i = 0; i < 10; i++) {
         client.sendWebSocketFrame("tesing " + std::to_string(i));
         LOG("Sending " << i);
         client.readRaw(response);
         LOG("Response: " << response);
         std::this_thread::sleep_for(std::chrono::seconds(1));
      }


      LOG("Found web SOCKET!!");
      return true;
   } else {
      return false;
   }
}
