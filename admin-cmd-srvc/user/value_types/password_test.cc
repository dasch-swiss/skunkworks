//
// Created by Ivan Subotic on 29/11/2020.
//

#include "catch2/catch.hpp"

#include "shared/xsd_types/xsd.h"

#include "password.h"

TEST_CASE("creating the password value type", "[entities][user][password]") {

  using namespace admin::user;

  SECTION("create password") {
    CHECK_NOTHROW(Password("abrakadabra"));
  }

}

