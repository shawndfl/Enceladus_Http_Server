#ifndef UNIT_TEST

#include <iostream>
#include "Enceladus.h"

bool Handler(ehs::HttpClientContext& client, const ehs::HttpServerContext& server) {

   LOGI("uri: " << client.request.getUri().c_str());
   LOGI("uriPath: " << client.request.getUriPath().c_str());
   LOGI("uriQuery: " << client.request.getUriQuery().c_str());

   std::string body = "<html><head><title>Testing</title></head><body> <b> Hello!!</b><br>";

   for (size_t i = 0; i < client.request.getQueryParameters().size(); i++) {
      ehs::Pair pair = client.request.getQueryParameters().at(i);

      body += pair.first + " = " + pair.second + "<br>";
   }

   body += "</body></html>";

   client.response.statusCode = ehs::HttpResponse::CODE200;

   client.response.appendHeader("Content-Type", "text/html; charset=ISO-8859-1");
   client.response.body = body;
   client.sendResponse();

   //LOGI("Is render initialized %i", render->isInitialized());
   return true;
}

int main(int argc, char *argv[]) {

   using namespace std::placeholders;

   ehs::Config::load("config/config.json");
   const ehs::Config& config = ehs::Config::get();

   ehs::HttpServer server;
   server.StartServer(config.listeningPort, config.threads);

   using namespace std::placeholders;

   // setup default handlers
   ehs::HttpHandleFile httpFiles;
   //ehs::HttpHandleWebSocket websockets;
   server.addRequestHandler(std::bind(&ehs::HttpHandleFile::Handler, httpFiles, _1, _2));
   //addRequestHandler(std::bind(&ehs::HttpHandleWebSocket::Handler, websockets, _1, _2));

   server.addRequestHandler(&Handler);

   server.JoinAcceptThread();

   LOGI("Exit ");

   return 0;
}

#endif
