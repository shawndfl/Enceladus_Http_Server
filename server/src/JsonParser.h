/*
 * JsonParser.h
 *
 *  Created on: Jun 1, 2020
 *      Author: sdady
 */

#ifndef SRC_JSONPARSER_H_
#define SRC_JSONPARSER_H_

#include "JsonNode.h"

class JsonParser {
public:
   JsonParser();
   virtual ~JsonParser();

   bool hasError() const;

   std::string getError() const;

   const JsonNode& parse(const std::string& json);

   const JsonNode& parseFile(const std::string& file);

private:

   /**
    * moves index_ and counts lines
    */
   bool eatWhiteSpace();

   /**
    * Eats whitespace until it finds a
    * char then returns the char
    */
   char peek() const;

   /**
    * Reads eats whitespace, collect characters until
    *  whitespace
    *  comma
    *
    */
   std::string getToken();

   bool processObject(JsonNode& node);

   bool processArray(JsonNode& node);

   bool isDelimiter(char ch);

   /**
    * Sets the error string and prepends the filename
    * and line number
    */
   void setError(const std::string& error);

   /**
    * Gets the string without quotes. returns false if no qoutes
    */
   bool getQuoted(const std::string& token, std::string& value) const;

   /**
    * gets a number from a token. If it cannot be converted it will return false
    */
   bool parseNumber(const std::string& token, double& value) const;

private:
   std::string json_;
   std::string token_;
   uint        index_;     /// The current char
   uint        line_;      /// The current line
   std::string error_;     /// The error message
   JsonNode    node_;      /// Root node
   std::string file_;      /// Json filename
};

#endif /* SRC_JSONPARSER_H_ */
