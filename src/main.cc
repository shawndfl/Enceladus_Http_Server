#ifndef UNIT_TEST

#include <iostream>
#include "Logging.h"
#include "HttpServer.h"
#include "HttpHandleFile.h"

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

   HttpServer server;
   server.StartServer(8080);

   HttpHandleFile httpFiles;
   server.addRequestHandler(std::bind(&HttpHandleFile::Handler, httpFiles, _1, _2));
   server.addRequestHandler(&Handler);

   server.JoinAcceptThread();

   LOGI("Exit ");

   return 0;
}

#endif
