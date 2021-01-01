//
// Created by Ivan Subotic on 29/12/2020.
//

#include "catch2/catch.hpp"
#include "external/nlohmann/json.hpp"

TEST_CASE("nlohmann_json tests", "[nlohmann_json|") {

  using namespace nlohmann;

  // create object from string literal
  json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;

  // or even nicer with a raw string literal
  auto j2 = R"(
    {
      "happy": true,
      "pi": 3.141
    }
  )"_json;

  CHECK(j == j2);
}