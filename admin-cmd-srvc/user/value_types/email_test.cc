//
// Created by Ivan Subotic on 29/11/2020.
//

#include <string>
#include "catch2/catch.hpp"
#include "shared/xsd_types/xsd.h"
#include "shared/error/error.h"
#include "email.h"

TEST_CASE("email value type", "[entities][user][email]") {

  using namespace std::string_literals; // enables s-suffix for std::string literals
  using namespace admin::user;

  SECTION("create") {
    CHECK(Email().empty());
    CHECK(Email("donald.duck@example.com").value() == "donald.duck@example.com"s);
    CHECK(Email(xsd::String("donald.duck@example.com"s)).value() == "donald.duck@example.com"s);
    CHECK(Email(Email("donald.duck@example.com")).value() == "donald.duck@example.com"s);
  }

  SECTION("direct assignments") {
    Email email;
    email = "donald.duck@example.com"s;
    CHECK(email.value() == "donald.duck@example.com"s);
  }

  SECTION("restrictions") {
    CHECK_THROWS_AS(Email("not_an_email"), xsd::Error);
  }

  SECTION("comparisons") {
    CHECK(Email("donald.duck@example.com"s) == Email("donald.duck@example.com"s));
  }

}


