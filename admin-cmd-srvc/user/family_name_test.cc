//
// Created by Ivan Subotic on 29/11/2020.
//

#include "catch2/catch.hpp"

#include "../../helpers/xsd_types/xsd.h"

#include "family_name.h"

TEST_CASE("family name value type", "[entities][user][family_name]") {

  using namespace admin::user;

  SECTION("create family name") {
    CHECK_NOTHROW(FamilyName("Duck"));
    CHECK(FamilyName("Duck").value() == "Duck");
    CHECK(FamilyName("Duck") == FamilyName("Duck"));
  }

}


