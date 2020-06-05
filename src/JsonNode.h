/*
 * JsonNode.h
 *
 *  Created on: Jun 1, 2020
 *      Author: sdady
 */

#ifndef SRC_JSONNODE_H_
#define SRC_JSONNODE_H_

#include <map>
#include <vector>
#include <string>

class JsonNode {
public:
   enum Type{
      JsonNull,
      JsonObject,
      JsonArray,
      JsonString,
      JsonNumber,
      JsonTrue,
      JsonFalse
   };
   JsonNode();
   virtual ~JsonNode();

   /**
    * set value for string type
    */
   void set(const std::string& value);

   /**
    * sets value for number type
    */
   void set(double value);

   /**
    * Sets true
    */
   void setBool(bool value);

   /**
    * Sets null
    */
   void setNull();

   /**
    * Sets value for object
    */
   void set(const std::string& key, const JsonNode& value);

   /**
    * Sets value in array
    */
   void set(int index, const JsonNode& value);

   /**
    * Creates an element at the end of an array
    */
   JsonNode& append();

   /**
    * Clears both arrays and objects
    */
   void clear();

   /**
    * Gets the string value of this node
    */
   std::string toString(bool humanReadable = false) const;

   JsonNode& operator[](int index);

   JsonNode& operator[](const std::string& key);

   JsonNode& operator=(int value);

   JsonNode& operator=(uint value);

   JsonNode& operator=(ulong value);

   JsonNode& operator=(long value);

   JsonNode& operator=(double value);

   JsonNode& operator=(const char* value);

   JsonNode& operator=(const std::string& value);

private:

   void toStringImpl(std::string& json) const;

   void toStringReadableImpl(std::string& json, int tab) const;
private:

   Type                             type_;

   std::string                      valueStr_;
   double                           valueNum_;
   std::vector<JsonNode>            valueArray_;
   std::map<std::string, JsonNode>  valueObj_;

};

#endif /* SRC_JSONNODE_H_ */
