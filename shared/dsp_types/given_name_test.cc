//
// Created by Ivan Subotic on 29/11/2020.
//

#include <string>
#include "catch2/catch.hpp"
#include "shared/xsd_types/xsd.h"
#include "given_name.h"

TEST_CASE("given name value type", "[entities][user][given_name]") {

  using namespace std::string_literals; // enables s-suffix for std::string literals
  using namespace dsp;

  SECTION("create") {
    CHECK(GivenName().empty());
    CHECK(GivenName("Donald").value() == "Donald"s);
    CHECK(GivenName(xsd::String("Donald"s)).value() == "Donald"s);
    CHECK(GivenName(GivenName("Donald")).value() == "Donald"s);
  }

  SECTION("direct assignments") {
    GivenName given_name;
    given_name = "Donald"s;
    CHECK(given_name.value() == "Donald"s);
  }

  SECTION("restrictions") {
    // CHECK_THROWS_AS(GivenName("d"), xsd::Error);
  }

  SECTION("comparisons") {
    CHECK(GivenName("Donald"s) == GivenName("Donald"s));
  }

}


