//
// Created by Ivan Subotic on 29/11/2020.
//

#include <string>
#include "catch2/catch.hpp"
#include "shared/xsd_types/xsd.h"
#include "shared/error/error.h"
#include "family_name.h"

TEST_CASE("family name value type", "[admin][user][family_name]") {

  using namespace std::string_literals; // enables s-suffix for std::string literals
  using namespace admin::user;

  SECTION("create") {
    CHECK(FamilyName().empty());
    CHECK(FamilyName("Duck").value() == "Duck"s);
    CHECK(FamilyName(xsd::String("Duck"s)).value() == "Duck"s);
    CHECK(FamilyName(FamilyName("Duck")).value() == "Duck"s);
  }

  SECTION("direct assignments") {
    FamilyName family_name;
    family_name = "New family name"s;
    CHECK(family_name.value() == "New family name"s);
  }

  SECTION("restrictions") {
    // CHECK_THROWS_AS(FamilyName("d"), dsp::Error);
  }

  SECTION("comparisons") {
    CHECK(FamilyName("Duck"s) == FamilyName("Duck"s));
  }

}


