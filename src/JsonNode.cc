/*
 * JsonNode.cc
 *
 *  Created on: Jun 1, 2020
 *      Author: sdady
 */

#include "JsonNode.h"

/*************************************************/
JsonNode::JsonNode() {
   type_ = JsonNull;
   valueNum_ = 0;
}

/*************************************************/
JsonNode::~JsonNode() {

}

/*************************************************/
void JsonNode::set(const std::string& value) {
}

/*************************************************/
void JsonNode::set(double value) {
   type_= JsonNumber;
   valueNum_ = value;
}

/*************************************************/
void JsonNode::setTrue() {
   type_= JsonTrue;
}

/*************************************************/
void JsonNode::setFalse() {
   type_= JsonFalse;
}

/*************************************************/
void JsonNode::setNull() {
   type_= JsonFalse;
}

/*************************************************/
void JsonNode::set(const std::string& key, const JsonNode& value) {
   type_= JsonObject;
   valueObj_[key] = value;
}

/*************************************************/
void JsonNode::set(int index, const JsonNode& value) {
   type_= JsonArray;
   valueArray_[index] = value;
}

/*************************************************/
void JsonNode::append(const JsonNode& value) {
   type_= JsonArray;
   valueArray_.push_back(value);
}

/*************************************************/
void JsonNode::clear() {
   valueArray_.clear();
   valueObj_.clear();
}

/*************************************************/
std::string JsonNode::toString() const {

   std::string json;

   // we can only start with objects or arrays
   if (type_ == JsonObject) {
      json = "{";
      toStringImpl(json);
      json += "}";
   } else if (type_ == JsonArray) {
      json = "[";
      toStringImpl(json);
      json += "]";
   } else {
      json = "{}";
   }
   return json;
}

/*************************************************/
void JsonNode::toStringImpl(std::string& string) const {
   switch (type_) {
   case JsonNull:
      string += "null";
      break;
   case JsonObject: {
      size_t i = 0;
      for (auto pair : valueObj_) {
         string += "\"" + pair.first + "\"=";
         pair.second.toStringImpl(string);
         if (i < valueObj_.size() - 1) {
            string += ",";
         }
         i++;
      }
      break;
   }
   case JsonArray:
      break;
   case JsonTrue:
         break;
   case JsonFalse:
         break;
   case JsonString:
         break;
   case JsonNumber:
      try {
         string += std::to_string(valueNum_);
      } catch(std::exception& ) {
         string += "0";
      }
      break;
   }
}
