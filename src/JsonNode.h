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
   void setTrue();
   /**
    * Sets false
    */
   void setFalse();
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
    * Adds to the end of an array
    */
   void append(const JsonNode& value);

   /**
    * Clears both arrays and objects
    */
   void clear();

   /**
    * Gets the string value of this node
    */
   std::string toString() const;

private:
   void toStringImpl(std::string& string) const;

private:

   Type                             type_;

   std::string                      valueStr_;
   double                           valueNum_;
   std::vector<JsonNode>            valueArray_;
   std::map<std::string, JsonNode>  valueObj_;

};

#endif /* SRC_JSONNODE_H_ */
