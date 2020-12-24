//
// Created by Ivan Subotic on 29/11/2020.
//

#include "catch2/catch.hpp"

#include "helpers/xsd_types/xsd.h"

#include "token.h"

TEST_CASE("creating the token value type", "[entities][user][token]") {

  using namespace entities::user;

  SECTION("create password") {
    CHECK_NOTHROW(Token());
  }

}


