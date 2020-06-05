/*
 * JsonParser.cc
 *
 *  Created on: Jun 1, 2020
 *      Author: sdady
 */

#include "JsonParser.h"
#include <sstream>
#include "Logging.h"

constexpr const char* whiteSpace = "\r\n\t ";
constexpr const char* startArray = "[";
constexpr const char* endArray = "]";
constexpr const char* startObject = "{";
constexpr const char* endObject = "}";
constexpr const char* assigment = ":";
constexpr const char* comma = ",";
constexpr const char* quote = "\"";

/*************************************************/
JsonParser::JsonParser() {
   index_ = 0;
   line_ = 0;
   error_ = "";
}

/*************************************************/
JsonParser::~JsonParser() {

}

/*************************************************/
const JsonNode& JsonParser::parse(const std::string& json) {
   json_ = json;
   file_ = "";
   index_ = 0;
   line_ = 0;
   error_ = "";
   token_ = "";
   node_.clear();

   while (true) {
      std::string token = getToken();
      if(token.size() == 0) {
         break;
      }
      LOG("Line: " << line_ << " Token: \'" << token << "\'");
   }

   return node_;
#if 0
   std::string token = getToken();
   if(token == "{") {
      processObject(node_);
   } else if(token == "[") {
      processArray(node_);
   } else {
      setError("expected object or array");
   }

   return node_;
#endif
}

/*************************************************/
const JsonNode& JsonParser::parseFile(const std::string& file) {
   //json_ =
   file_ = file;
   index_ = 0;
   line_ = 0;
   error_ = "";
   token_ = "";
   node_.clear();
   return node_;
}

/*************************************************/
bool JsonParser::eatWhiteSpace() {
   bool hasWhiteSpace = false;
   while(json_[index_] == ' '  || json_[index_] == '\t' ||
         json_[index_] == '\n' || json_[index_] == '\r' ) {

      index_++;

      if(json_[index_] == '\n' || json_[index_] == '\r' ) {
         line_++;
      }
      hasWhiteSpace = true;
   }

   return hasWhiteSpace;
}

/*************************************************/
char JsonParser::peek() const {
   LOG("i=" << index_ << " size: " << json_.size());

   if(index_ + 1 < json_.size()) {
      return json_[index_ + 1];
   } else {
      return '\0';
   }
}

/*************************************************/
std::string JsonParser::getToken() {
   eatWhiteSpace();
   token_ = "";
   char ch = json_[index_];

   if(ch =='\"') {

      // collect the token until a " is found
      for (index_++; index_ < json_.size(); index_++) {
         ch = json_[index_];

         // keep track of new lines
         if (ch == '\r' || ch == '\n') {
            line_++;
         }

         // done
         if (ch == '\"') {
            index_++;   // eat the quote
            break;
         }

         token_ += ch;
      }
   } else if (isDelimiter(ch)) {
      // single token
      token_ = ch;
      index_++;

   } else {

      // collect the token until a delimiter
      for (; index_ < json_.size(); index_++) {
         ch = json_[index_];

         // keep track of new lines
         if (ch == '\r' || ch == '\n') {
            line_++;
         }

         // done
         if (isDelimiter(ch)) {
            break;
         }

         token_ += ch;
      }
   }

   return token_;
}

/*************************************************/
void JsonParser::processObject(JsonNode& node) {
   std::string token = getToken();
   while (token .size()) {
      token = getToken();
      LOG("Line: " << line_ << " Token: \'" << token << "\'");
   }
}

/*************************************************/
void JsonParser::processArray(JsonNode& node) {

}

/*************************************************/
bool JsonParser::hasError() const {
   return error_.size() > 0;
}

/*************************************************/
std::string JsonParser::getError() const {
   return error_;
}

/*************************************************/
bool JsonParser::isDelimiter(char ch) {
   return ch == '\n' || ch == '\r'  || ch == ' '  || ch == '\t'  ||
          ch == ','  || ch == '{'   || ch == '}'  || ch == '['   ||
          ch == ']'  || ch == ':'   || ch == '\"';
}

void JsonParser::setError(const std::string& error) {
   std::stringstream str;
   str << file_ << " ("  << line_ << ") " << error;
   error_ = str.str();
}
