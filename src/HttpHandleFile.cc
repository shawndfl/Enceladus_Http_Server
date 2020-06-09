/*
 * HttpHandleFile.cc
 *
 *  Created on: Jun 6, 2020
 *      Author: sdady
 */

#include "HttpHandleFile.h"
#include "Logging.h"
#include "HttpFileSystem.h"
#include <fstream>

/*************************************************/
HttpHandleFile::HttpHandleFile() {
}

/*************************************************/
HttpHandleFile::~HttpHandleFile() {
}

/*************************************************/
bool HttpHandleFile::Handler(HttpClientContext& client, const HttpServerContext& server) {
   bool handled = false;
   std::string path = "http/content/" + client.request.getUriPath();
   std::string ext = HttpFileSystem::getExtenion(path);
   if(HttpFileSystem::exists(path)) {
      std::ifstream t(path);
      std::string body;

      t.seekg(0, std::ios::end);
      body.reserve(t.tellg());
      t.seekg(0, std::ios::beg);

      body.assign((std::istreambuf_iterator<char>(t)),
                  std::istreambuf_iterator<char>());

      client.response.body = body;
      client.response.statusCode = HttpResponse::CODE202;
      client.SendResponse();
      handled = true;
   }

   return handled;
}
