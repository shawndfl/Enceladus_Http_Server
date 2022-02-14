#ifndef UNIT_TEST

#include <iostream>
#include "Logging.h"
#include "HttpServer.h"
#include "Config.h"

bool Handler(HttpClientContext& client, const HttpServerContext& server) {

   LOGI("uri: %s", client.request.getUri().c_str());
   LOGI("uriPath: %s", client.request.getUriPath().c_str());
   LOGI("uriQuery: %s", client.request.getUriQuery().c_str());

   std::string body = "<html><head><title>Testing</title></head><body> <b> Hello!!</b><br>";

   for (size_t i = 0; i < client.request.getQueryParameters().size(); i++) {
      Pair pair = client.request.getQueryParameters().at(i);

      body += pair.first + " = " + pair.second + "<br>";
   }

   body += "</body></html>";

   client.response.statusCode = HttpResponse::CODE200;

   client.response.appendHeader("Content-Type", "text/html; charset=ISO-8859-1");
   client.response.body = body;
   client.SendResponse();

   //LOGI("Is render initialized %i", render->isInitialized());
   return true;
}

int main(int argc, char *argv[]) {

   using namespace std::placeholders;

   Config::load("../config/config.json");
   const Config& config = Config::get();

   HttpServer server;
   server.StartServer(config.listeningPort, config.threads);

   server.addRequestHandler(&Handler);

   server.JoinAcceptThread();

   LOGI("Exit ");

   return 0;
}

#endif
