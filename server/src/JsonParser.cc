/*
 * JsonParser.cc
 *
 *  Created on: Jun 1, 2020
 *      Author: sdady
 */

#include "JsonParser.h"
#include <sstream>
#include <fstream>
#include "Logging.h"

namespace ehs {

constexpr const char* whiteSpace = "\r\n\t ";
constexpr const char  startArray = '[';
constexpr const char  endArray = ']';
constexpr const char  startObject = '{';
constexpr const char  endObject = '}';
constexpr const char  assigment = ':';
constexpr const char  comma = ',';
constexpr const char*  quote = "\"\'";

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

   std::string token = getToken();
   if(token == "{") {
      processObject(node_);
   } else if(token == "[") {
      processArray(node_);
   } else {
      setError("expected object or array");
   }

   return node_;
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

   std::ifstream stream;
   stream.open(file);
   if(stream.is_open()) {
      std::stringstream sstream;
      sstream << stream.rdbuf();
      json_ = sstream.str();
      stream.close();

      std::string token = getToken();
      if (token == "{") {
         processObject(node_);
      } else if (token == "[") {
         processArray(node_);
      } else {
         setError("expected object or array");
      }
   } else {
      LOGD("Cannot open file " << file);
   }

   return node_;
}

/*************************************************/
bool JsonParser::eatWhiteSpace() {
   bool hasWhiteSpace = false;
   bool inComment = false;

   while(true) {

      // handle comment
      if (json_[index_] == '#') {
         inComment = true;
      }

      if(inComment) {
         if(json_[index_] == '\n' || json_[index_] == '\r' ) {
            inComment = false;
         }
      } else {
         // if not white space break
         if(json_[index_] != ' '  && json_[index_] != '\t' &&
            json_[index_] != '\n' && json_[index_] != '\r' ) {
            break;
         }
      }

      if(json_[index_] == '\n' || json_[index_] == '\r' ) {
         line_++;
      }

      index_++;


      // set the flag that some white space was found
      hasWhiteSpace = true;
   }

   return hasWhiteSpace;
}

/*************************************************/
char JsonParser::peek() const {
   if(index_ < json_.size()) {
      return json_[index_];
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

      // keep the quotes
      token_ += ch;

      // collect the token until a " is found
      for (index_++; index_ < json_.size(); index_++) {
         ch = json_[index_];

         // keep track of new lines
         if (ch == '\r' || ch == '\n') {
            line_++;
         }

         // collect the string including the last quote
         token_ += ch;

         // done
         if (ch == '\"') {
            index_++;   // eat the quote
            break;
         }
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
bool JsonParser::processObject(JsonNode& node) {
   while(true) {
      std::string key;
      std::string token;

      if(!getQuoted(getToken(), key)) {
         setError("Expected key in quotes");
         break;
      }

      token = getToken();

      // empty object return false
      // and the parent node will be set to null
      if (token == "}") {
         return false;
      }
      // non empty object will have a ":" next
      else if (token != ":") {
         setError("Expected \':\'");
         break;
      }


      std::string value = getToken();
      std::string unquoted;
      double numValue = 0;

      // new object
      if (value == "{") {
         JsonNode &object = node[key];
         if (!processObject(object)) {
            node.setNull();
         }
      }
      // new array
      else if (value == "[") {
         JsonNode &item = node.append();
         if (!processArray(item)) {
            node.setNull();
            break;
         }

      } else if (value == "true") {
         node[key].setBool(true);
      } else if (value == "false") {
         node[key].setBool(false);
      } else if (value == "null") {
         node[key].setNull();
      } else if (getQuoted(value, unquoted)) {
         node[key] = unquoted;
      } else if (parseNumber(value, numValue)) {
         node[key] = numValue;
      } else {
         setError("Value type must be number, \"string\", object, array, true, false, or null");
         break;
      }

      token = getToken();

      // done
      if(token == "}") {
         break;
      } else if(token != ",") {
         setError("Expected \',\'");
         break;
      }
   }
   return true;
}

/*************************************************/
bool JsonParser::processArray(JsonNode& node) {
   while (true) {

      std::string value = getToken();
      std::string unquoted;
      double numValue = 0;

      if (getToken() == "]") {
         node.setNull();
         return false;
      }

      // new object
      if (value == "{") {
         JsonNode& object = node.append();
         processObject(object);
         // new array
      } else if (value == "[") {
         JsonNode& array = node.append();
         processArray(array);

      } else if (value == "true") {
         node.append().setBool(true);
      } else if (value == "false") {
         node.append().setBool(false);
      } else if (value == "null") {
         node.append().setNull();
      } else if (getQuoted(value, unquoted)) {
         node.append() = unquoted;
      } else if (parseNumber(value, numValue)) {
         node.append() = numValue;
      }

      std::string token = getToken();

      // done
      if (token == "]") {
         break;
      } else if (token != ",") {
         setError("Expected \',\'");
         break;
      }
   }
   return true;
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

/*************************************************/
void JsonParser::setError(const std::string& error) {
   std::stringstream str;
   str << file_ << " ("  << line_ << ") " << error;
   error_ = str.str();
}

/*************************************************/
bool JsonParser::getQuoted(const std::string& token, std::string& value) const {
   if(token.size() > 2) {
      if(token[0] == '\"' && token[token.size() - 1] == '\"'){
         value = token.substr(1, token.size() - 2);
         return true;
      }
   }

   return false;
}

/*************************************************/
bool JsonParser::parseNumber(const std::string& token, double& value) const {
   try{
      size_t index = 0;
      value = std::stod(token, &index);

      // make sure the whole token is used
      if(index != token.size()) {
         return false;
      } else {
         return true;
      }
   } catch(std::exception& ex) {
      return false;
   }
}
}
