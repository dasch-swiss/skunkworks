//
// Created by Ivan Subotic on 29/11/2020.
//

#include "catch2/catch.hpp"

#include "helpers/xsd_types/xsd.h"

#include "identifier.h"

TEST_CASE("creating the identifier value type", "[entities][user][identifier]") {

  using namespace entities::user;

  SECTION("create identifier") {
    CHECK_NOTHROW(Identifier());
  }

}


