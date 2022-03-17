#ifndef UNIT_TEST

#include <iostream>
#include "Enceladus.h"

int main(int argc, char *argv[]) {

   using namespace std::placeholders;

   // load the config file
   ehs::Config::load("config.json");
   const ehs::Config& config = ehs::Config::get();

   // start the server
   ehs::HttpServer server;
   server.StartServer(config.listeningPort, config.threads);

   // setup default file handler
   ehs::HttpHandleFile httpFiles(config.content);

   // add the handler to the server
   server.addRequestHandler(std::bind(&ehs::HttpHandleFile::Handler, httpFiles, _1, _2));

   // wait for clients
   server.JoinAcceptThread();

   return 0;
}

#endif
