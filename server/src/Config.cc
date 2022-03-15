/*
 * Config.cc
 *
 *  Created on: Feb 1, 2022
 *      Author: shawn
 */

#include "Config.h"
#include "JsonParser.h"

Config Config::config_;

/*************************************************/
Config::Config() {
   listeningPort    = 80;
   cert             = "";
   pass             = "";
   threads          = 10;
   content          = "../http";
}

/*************************************************/
Config::~Config() {
}

/*************************************************/
const Config& Config::load(const std::string &jsonFilename) {
   JsonParser parser;
   JsonNode node = parser.parseFile(jsonFilename);

   config_.listeningPort      = node.getNumber("listeningPort",       config_.listeningPort);
   config_.cert               = node.getString("cert",                config_.cert);
   config_.pass               = node.getString("pass",                config_.pass);
   config_.threads            = node.getNumber("threads",             config_.threads);
   config_.content            = node.getString("content",             config_.content);

   return get();
}

/*************************************************/
const Config& Config::get() {
   return config_;
}


