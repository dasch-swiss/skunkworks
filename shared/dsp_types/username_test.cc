//
// Created by Ivan Subotic on 29/11/2020.
//

#include <string>
#include "catch2/catch.hpp"
#include "shared/xsd_types/xsd.h"
#include "shared/error/error.h"
#include "username.h"

TEST_CASE("creating the username value type", "[entities][user][username]") {

  using namespace std::string_literals; // enables s-suffix for std::string literals
  using namespace admin::user;

  SECTION("create") {
    CHECK(Username().empty());
    CHECK(Username("dduck").value() == "dduck"s);
    CHECK(Username(xsd::String("dduck"s)).value() == "dduck"s);
    CHECK(Username(Username("dduck")).value() == "dduck"s);
  }

  SECTION("direct assignments") {
    Username username;
    username = "dduck"s;
    CHECK(username.value() == "dduck"s);

    username = Username("daisyduck");
    CHECK(username.value() == "daisyduck");
  }


  // allowed length is 4 - 50 characters long
  SECTION("restrictions - length") {

    // username has 3 characters
    // CHECK_THROWS_AS(Username("abc"), xsd::Error);

    // username has 4 characters
    CHECK_NOTHROW(Username("root"));

    // username has 50 characters
    CHECK_NOTHROW(Username("12345678901234567890123456789012345678901234567890"));

    // username has 51 characters
    // CHECK_THROWS_AS(Username("123456789012345678901234567890123456789012345678901"), xsd::Error);
  }

  // Only contains alphanumeric characters
  SECTION("restrictions - allowed characters") {
    // username has not allowed characters
    // CHECK_THROWS_AS(admin::user::Username("abc123._"), xsd::Error);
  }

  SECTION("comparisons") {
    CHECK(Username("dduck"s) == Username("dduck"s));
  }

}


