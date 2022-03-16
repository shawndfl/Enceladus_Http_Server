#include "UnitTest++/UnitTest++.h"
#include "Enceladus.h"

SUITE(Json) {

/*************************************************/
TEST(ToString) {
   ehs::JsonNode node;
   ehs::JsonNode value;
   value.setNumber(12);
   node.setObject("test", value);
   CHECK_EQUAL("{\"test\":12.000000}", node.toString());

}

/*************************************************/
TEST(Array) {
   ehs::JsonNode node;
   node.append() = 12;
   node.append() = 13;
   CHECK_EQUAL("[12.000000,13.000000]", node.toString());

}

/*************************************************/
TEST(DeepObjects) {
   ehs::JsonNode object;

   ehs::JsonNode& array = object["array"];
   array.append() = "testing1";
   array.append() = "testing2";
   array.append() = "testing3";

   object["number"] = 52.45;

   object["string"] = "hello";

   object["bool_true"].setBool(true);

   object["boo_false"].setBool(false);

   object["null"].setNull();

   ehs::JsonNode& object2 = object["sub_object"];
   object2["item1"] = 45;
   object2["item2"] = "testing";
   object2["item3"] = "testing";

   ehs::JsonNode& array2 = object2["item4"];
   array2[3] = 9;

   //LOGD(object.toString());
   //LOGD("\n" << object.toString(true));

}

TEST(ParseCompare) {
   ehs::JsonNode object;

   ehs::JsonNode& array = object["array"];
   array.append() = "testing1";
   array.append() = "testing2";
   array.append() = "testing3";

   object["number"] = 52.45;

   object["string"] = "hello";

   object["bool_true"].setBool(true);

   object["boo_false"].setBool(false);

   object["null"].setNull();

   ehs::JsonNode& object2 = object["sub_object"];
   object2["item1"] = 45;
   object2["item2"] = "testing";
   object2["item3"] = "testing";

   ehs::JsonNode& array2 = object2["item4"];
   array2[3] = 9;

   ehs::JsonParser parser;
   ehs::JsonNode data = parser.parse(object.toString(true));

   CHECK_EQUAL(object.toString(), data.toString());

}


TEST(Parse) {
   ehs::JsonParser parser;
   ehs::JsonNode data = parser.parse("{}");

   CHECK_EQUAL("{}", data.toString(true));

   data = parser.parse("{\n\n key:2 }");

   CHECK_EQUAL(true, parser.hasError());

   CHECK_EQUAL(" (2) Expected key in quotes", parser.getError());
}


TEST(ParseError) {
   ehs::JsonParser parser;

   ehs::JsonNode data = parser.parse("{\n \"key\":2,\n\"key2\"\n  : 7,  }");

   CHECK_EQUAL(true, parser.hasError());

   CHECK_EQUAL(" (3) Expected key in quotes", parser.getError());
}

TEST(ParseErrorAssigment) {
   ehs::JsonParser parser;

   ehs::JsonNode data = parser.parse("{\n \"key\" 2,\n\"key2\"\n  : 7,  }");

   CHECK_EQUAL(true, parser.hasError());

   CHECK_EQUAL(" (1) Expected \':\'", parser.getError());

   data = parser.parse("{\n \"key\": 2, \n \"key2\"\n  : 7a,  }");

   CHECK_EQUAL(true, parser.hasError());

   CHECK_EQUAL(" (3) Value type must be number, \"string\", object, array, true, false, or null", parser.getError());
}

}
