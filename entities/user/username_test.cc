//
// Created by Ivan Subotic on 29/11/2020.
//

#include "catch2/catch.hpp"

#include "helpers/xsd_types/xsd.h"

#include "entities/error.h"
#include "username.h"

TEST_CASE("creating the username value type", "[entities][user][username]") {

  using namespace entities::user;

  SECTION("create username") {
    CHECK(Username("dduck").value()=="dduck");
  }

  // allowed length is 4 - 50 characters long
  SECTION("length restrictions") {

  // username has 3 characters
    CHECK_THROWS_AS(Username("abc"), xsd::Error);

  // username has 4 characters
    CHECK_NOTHROW(Username("root"));

  // username has 50 characters
    CHECK_NOTHROW(Username("12345678901234567890123456789012345678901234567890"));

  // username has 51 characters
    CHECK_THROWS_AS(Username("123456789012345678901234567890123456789012345678901"), xsd::Error);
  }

  // Only contains alphanumeric characters
  SECTION("allowed characters") {
    // username has not allowed characters
    CHECK_THROWS_AS(entities::user::Username("abc123._"), xsd::Error);
  }

}


