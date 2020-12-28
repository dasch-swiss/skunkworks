//
// Created by Ivan Subotic on 29/11/2020.
//

#include "catch2/catch.hpp"

#include "../../../helpers/xsd_types/xsd.h"

#include "email.h"

TEST_CASE("creating the email value type", "[entities][user][email]") {

  using namespace admin::user;

  SECTION("create email") {
    CHECK_NOTHROW(Email("dduck@example.com"));
    CHECK(Email("dduck@example.com").value() == "dduck@examle.com");
  }

}


