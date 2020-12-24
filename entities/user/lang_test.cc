//
// Created by Ivan Subotic on 29/11/2020.
//

#include "catch2/catch.hpp"

#include "helpers/xsd_types/xsd.h"

#include "lang.h"

TEST_CASE("creating the lang value type", "[entities][user][lang]") {

  using namespace entities::user;

  SECTION("create lang") {
    CHECK_NOTHROW(Lang("en"));
  }

}


