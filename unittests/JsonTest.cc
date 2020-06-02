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

}
