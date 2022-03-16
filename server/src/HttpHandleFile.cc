/*
 * HttpHandleFile.cc
 *
 *  Created on: Jun 6, 2020
 *      Author: sdady
 */

#include "HttpHandleFile.h"
#include "Logging.h"
#include "HttpFileSystem.h"
#include "Config.h"
#include <fstream>

namespace ehs {
/*************************************************/
HttpHandleFile::HttpHandleFile() {
}

/*************************************************/
HttpHandleFile::~HttpHandleFile() {
}

/*************************************************/
bool HttpHandleFile::Handler(HttpClientContext& client, const HttpServerContext& server) {
   bool handled = false;
   const Config& config = Config::get();

   std::string path = config.content + client.request.getUriPath();
   std::string ext = HttpFileSystem::getExtenion(path);

   // TODO check absolute path

   if(HttpFileSystem::exists(path)) {
      std::ifstream t(path);

      // error but it was handled
      if(!t.is_open()) {
         return true;
      }
      std::string body;

      t.seekg(0, std::ios::end);
      body.reserve(t.tellg());
      t.seekg(0, std::ios::beg);

      body.assign((std::istreambuf_iterator<char>(t)),
                  std::istreambuf_iterator<char>());

      // set the content type
      if (ext == ".html") {
         client.response.appendHeader("Content-Type", "text/html");
      } else if (ext == ".json") {
         client.response.appendHeader("Content-Type", "application/json");
      } else if (ext == ".js") {
         client.response.appendHeader("Content-Type", "application/javascript");
      } else if (ext == ".png") {
         client.response.appendHeader("Content-Type", "image/png");
      } else if (ext == ".jpg") {
         client.response.appendHeader("Content-Type", "text/jpg");
      } else {
         client.response.appendHeader("Content-Type", "text/plain");
      }

      client.response.body = body;

      client.response.appendHeader("X-Content-Type-Options", "nosniff");
      client.response.statusCode = HttpResponse::CODE200;
      client.sendResponse();
      handled = true;
   }

   return handled;
}
}
