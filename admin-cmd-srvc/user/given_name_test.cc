//
// Created by Ivan Subotic on 29/11/2020.
//

#include "catch2/catch.hpp"

#include "../../helpers/xsd_types/xsd.h"

#include "given_name.h"

TEST_CASE("creating the given name value type", "[entities][user][given_name]") {

  using namespace entities::user;

  SECTION("create given name") {
    CHECK_NOTHROW(GivenName("Donald"));
  }

}


