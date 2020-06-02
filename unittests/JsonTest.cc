#include "UnitTest++/UnitTest++.h"
#include "Logging.h"
#include "JsonNode.h"

SUITE(Json){
   TEST(ToString) {
      JsonNode node;
      JsonNode value;
      value.set(12);
      node.set("test", value);
      LOG("Json: " << node.toString());

   }

   TEST(Array) {
        JsonNode node;
        node.append() = 12;
        node.append() = 13;
        //JsonNode& value1 = node.append();
        //JsonNode& value2 = node.append();
        //value1 = 12;
        //value2 = 13;
        LOG("Json: " << node.toString());

     }

}
