//
// Created by Ivan Subotic on 29/11/2020.
//

#include <string>
#include "catch2/catch.hpp"
#include "shared/xsd_types/xsd.h"
#include "shared/error/error.h"
#include "password.h"

TEST_CASE("password value type", "[entities][user][password]") {

  using namespace std::string_literals; // enables s-suffix for std::string literals
  using namespace dsp;

  SECTION("create") {
    CHECK(Password().empty());
    CHECK(Password("abrakadabra"s).value() == "abrakadabra"s);
    CHECK(Password(xsd::String("abrakadabra"s)).value() == "abrakadabra"s);
    CHECK(Password(Password("abrakadabra")).value() == "abrakadabra"s);
  }

  SECTION("direct assignments") {
    Password password;
    password = "abrakadabra"s;
    CHECK(password.value() == "abrakadabra"s);
  }

  SECTION("restrictions") {
    // CHECK_THROWS_AS(Password("abr"), dsp::Error);
  }

  SECTION("comparisons") {
    CHECK(Password("abrakadabra"s) == Password("abrakadabra"s));
  }

}


