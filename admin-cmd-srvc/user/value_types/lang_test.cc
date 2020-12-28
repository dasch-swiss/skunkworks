//
// Created by Ivan Subotic on 29/11/2020.
//

#include "catch2/catch.hpp"

#include "helpers/xsd_types/xsd.h"

#include "lang.h"

TEST_CASE("lang value type", "[admin][user][lang]") {

  using namespace admin::user;

  SECTION("create lang") {
    CHECK_NOTHROW(Lang("en"));
  }

}


