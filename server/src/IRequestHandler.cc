/*
 * IRequestHandler.cc
 *
 *  Created on: Mar 25, 2022
 *      Author: shawn
 */

#include "IRequestHandler.h"

namespace ehs {

/*************************************************/
bool IRequestHandler::handler(HttpClientContext &client, const HttpServerContext &server) {

   return false;
}

/*************************************************/
bool IRequestHandler::onOpen(HttpClientContext &client, const HttpServerContext &server) {
   return false;
}

/*************************************************/
bool IRequestHandler::onMessage(HttpClientContext &client, const HttpServerContext &server) {
   return false;
}

/*************************************************/
bool IRequestHandler::onClose(HttpClientContext &client, const HttpServerContext &server) {
   return false;
}

/*************************************************/
IRequestHandler::IRequestHandler() {

}

/*************************************************/
IRequestHandler::~IRequestHandler() {
}

} /* namespace ehs */
