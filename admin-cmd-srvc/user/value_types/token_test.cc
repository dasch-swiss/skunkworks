//
// Created by Ivan Subotic on 29/11/2020.
//

#include "catch2/catch.hpp"
#include "shared/error/error.h"
#include "shared/xsd_types/xsd.h"
#include "token.h"

TEST_CASE("creating the token value type", "[entities][user][token]") {

  using namespace std::string_literals; // enables s-suffix for std::string literals
  using namespace admin::user;

  SECTION("create") {
    CHECK(Token().empty());
    CHECK(Token("1234567890").value() == "1234567890"s);
    CHECK(Token(xsd::String("1234567890"s)).value() == "1234567890"s);
    CHECK(Token(Token("1234567890")).value() == "1234567890"s);
  }

  SECTION("direct assignments") {
    Token token;
    token = "New token"s;
    CHECK(token.value() == "New token"s);
  }

  SECTION("restrictions") {
    // CHECK_THROWS_AS(Token("123456789"), dsp::Error);
  }

  SECTION("comparisons") {
    CHECK(Token("1234567890"s) == Token("1234567890"s));
  }

}


