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
void JsonNode::clear() {
   valueArray_.clear();
   valueObj_.clear();
}

/*************************************************/
std::string JsonNode::toString() const {

   std::string json;

   // we can only start with objects or arrays
   if (type_ == JsonObject) {
      toStringImpl(json);
   } else if (type_ == JsonArray) {
      toStringImpl(json);
   } else {
      json = "{}";
   }
   return json;
}

/*************************************************/
void JsonNode::toStringImpl(std::string& json) const {
   switch (type_) {
   case JsonNull:
      json += "null";
      break;
   case JsonObject: {
      size_t i = 0;
      json += "{";
      for (auto& pair : valueObj_) {
         json += "\"" + pair.first + "\"=";
         pair.second.toStringImpl(json);
         if (i < valueObj_.size() - 1) {
            json += ",";
         }
         i++;
      }
      json += "}";
      break;
   }
   case JsonArray: {
        size_t i = 0;
        json += "[";
        for (auto& pair : valueObj_) {
           pair.second.toStringImpl(json);
           if (i < valueObj_.size() - 1) {
              json += ",";
           }
           i++;
        }
        json += "]";
        break;
     }
      break;
   case JsonTrue:
         json += "true";
         break;
   case JsonFalse:
         json += "false";
         break;
   case JsonString:
      json += "\"" + valueStr_ + "\"";
         break;
   case JsonNumber:
      try {
         json += std::to_string(valueNum_);
      } catch(std::exception& ) {
         json += "0";
      }
      break;
   }
}

/*************************************************/
JsonNode& JsonNode::append() {
   type_= JsonArray;
   valueArray_.push_back(std::move(JsonNode()));
   return valueArray_[valueArray_.size() - 1];
}

/*************************************************/
JsonNode& JsonNode::operator [](int index) {
   type_= JsonArray;
   JsonNode newNode;
   for(int i = valueArray_.size(); i <= index; i++){
      valueArray_.push_back(JsonNode());
   }
   return valueArray_[index];
}

/*************************************************/
JsonNode& JsonNode::operator [](const std::string& key) {
   type_= JsonObject;
   return valueObj_[key];
}

/*************************************************/
JsonNode& JsonNode::operator =(ulong value) {
   type_= JsonNumber;
   valueNum_ = value;
   return *this;
}

/*************************************************/
JsonNode& JsonNode::operator =(bool value) {
   type_ = value ? JsonTrue: JsonFalse;
   return *this;
}


/*************************************************/
JsonNode& JsonNode::operator =(int value) {
   type_= JsonNumber;
   valueNum_ = value;
   return *this;
}

/*************************************************/
JsonNode& JsonNode::operator =(uint value) {
   type_= JsonNumber;
   valueNum_ = value;
   return *this;
}

/*************************************************/
JsonNode& JsonNode::operator =(long value) {
   type_= JsonNumber;
   valueNum_ = value;
   return *this;
}

/*************************************************/
JsonNode& JsonNode::operator =(double value) {
   type_= JsonNumber;
   valueNum_ = value;
   return *this;
}

/*************************************************/
JsonNode& JsonNode::operator =(const std::string& value) {
   type_= JsonString;
   valueStr_ = value;
   return *this;
}
