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
void JsonNode::setBool(bool value) {
   type_= value?  JsonTrue: JsonFalse;
}

/*************************************************/
void JsonNode::setNull() {
   type_= JsonNull;
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
std::string JsonNode::toString(bool humanReadable) const {

   std::string json;

   // we can only start with objects or arrays
   if (type_ == JsonObject || type_ == JsonArray) {
      if(humanReadable){
         toStringReadableImpl(json, 0);
      } else {
         toStringImpl(json);
      }
   } else {
      json = "{}";
   }
   return json;
}

/*************************************************/
void JsonNode::toStringReadableImpl(std::string& json, int tab) const {
   std::string tabs;
   for(int i =0; i < tab; i++) {
      tabs +="\t";
   }

   switch (type_) {
      case JsonNull:
         json += "null";
         break;
      case JsonObject: {
         size_t i = 0;
         json += "{\n";
         ++tab;
         for (auto& pair : valueObj_) {
            json += tabs + "\t\"" + pair.first + "\": ";
            pair.second.toStringReadableImpl(json, tab);
            if (i < valueObj_.size() - 1) {
               json += ",";
            }
            i++;
            json += '\n';
         }
         json += tabs + "}";
         break;
      }
      case JsonArray: {
           size_t i = 0;
           json += "[\n";
           ++tab;
           for (auto& item : valueArray_) {
              json += tabs + "\t";
              item.toStringReadableImpl(json, tab);
              if (i < valueArray_.size() - 1) {
                 json += ",";
              }
              i++;
              json += '\n';
           }
           json += tabs + "]";
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
void JsonNode::toStringImpl(std::string& json) const {
   switch (type_) {
   case JsonNull:
      json += "null";
      break;
   case JsonObject: {
      size_t i = 0;
      json += "{";
      for (auto& pair : valueObj_) {
         json += "\"" + pair.first + "\":";
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
        for (auto& item : valueArray_) {
           item.toStringImpl(json);
           if (i < valueArray_.size() - 1) {
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

/*************************************************/
JsonNode& JsonNode::operator =(const char* value) {
   type_= JsonString;
   valueStr_ = value;
   return *this;
}
