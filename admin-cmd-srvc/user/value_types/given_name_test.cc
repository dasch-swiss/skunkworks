//
// Created by Ivan Subotic on 29/11/2020.
//

#include "catch2/catch.hpp"

#include "shared/xsd_types/xsd.h"

#include "given_name.h"

TEST_CASE("given name value type", "[entities][user][given_name]") {

  using namespace admin::user;

  SECTION("create given name") {
    CHECK_NOTHROW(GivenName("Donald"));
    CHECK(GivenName("Donald").value() == "Donald");
    CHECK(GivenName("Donald") == GivenName("Donald"));
  }

}


