//
// Created by Ivan Subotic on 29/11/2020.
//

#include "catch2/catch.hpp"

#include "shared/xsd_types/xsd.h"

#include "email.h"

TEST_CASE("email value type", "[entities][user][email]") {

  using namespace admin::user;

  SECTION("create email") {
    CHECK_NOTHROW(Email("dduck@example.com"));
    CHECK(Email("dduck@example.com").value() == "dduck@example.com");
  }

}


