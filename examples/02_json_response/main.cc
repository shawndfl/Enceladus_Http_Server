#ifndef UNIT_TEST

#include <iostream>
#include "Enceladus.h"

bool Handler(ehs::HttpClientContext& client, const ehs::HttpServerContext& server) {

   ehs::JsonNode node;

   node["user"][0]["name"] = "Bob";
   node["user"][0]["phone"] = "555-555-5555";

   node["user"][1]["name"] = "Sue";
   node["user"][1]["phone"] = "555-555-1234";

   client.response.statusCode = ehs::HttpResponse::CODE200;
   client.response.appendHeader("Content-Type", "application/json; charset=ISO-8859-1");
   client.response.body = node.toString();
   client.sendResponse();

   return true;
}

int main(int argc, char *argv[]) {

   using namespace std::placeholders;

   ehs::Config::load("config.json");
   const ehs::Config& config = ehs::Config::get();

   ehs::HttpServer server;
   server.StartServer(config.listeningPort, config.threads);

   // setup default handlers
   server.addRequestHandler(&Handler);

   server.JoinAcceptThread();

   return 0;
}

#endif
