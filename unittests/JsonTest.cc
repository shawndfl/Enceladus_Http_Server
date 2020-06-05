#include "UnitTest++/UnitTest++.h"
#include "Logging.h"
#include "JsonNode.h"

SUITE(Json){
   TEST(ToString) {
      JsonNode node;
      JsonNode value;
      value.set(12);
      node.set("test", value);
      CHECK_EQUAL("{\"test\":12.000000}", node.toString());

   }

   TEST(Array) {
        JsonNode node;
        node.append() = 12;
        node.append() = 13;
        CHECK_EQUAL("[12.000000,13.000000]", node.toString());

     }

   TEST(DeepObjects) {
           JsonNode object;

           JsonNode& array = object["array"];
           array.append() = "testing1";
           array.append() = "testing2";
           array.append() = "testing3";

           object["number"] = 52.45;

           object["string"] = "hello";

           object["bool_true"].setBool(true);

           object["boo_false"].setBool(false);

           object["null"].setNull();

           JsonNode& object2 = object["sub_object"];
           object2["item1"] = 45;
           object2["item2"] = "testing";
           object2["item3"] = "testing";

           JsonNode& array2 = object2["item4"];
           array2[3] = 9;

           LOG(object.toString());
           LOG("\n" << object.toString(true));


        }

}
