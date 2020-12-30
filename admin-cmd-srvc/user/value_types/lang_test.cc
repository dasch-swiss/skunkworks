//
// Created by Ivan Subotic on 29/11/2020.
//

#include "catch2/catch.hpp"

#include "shared/xsd_types/xsd.h"

#include "lang.h"

TEST_CASE("lang value type", "[admin][user][lang]") {

  using namespace admin::user;

  SECTION("create lang through default constructor (no provided value)") {
    CHECK_NOTHROW(Lang());
    CHECK(Lang().value().length() > 0);
    CHECK(Lang().value() == "en");
  }

  SECTION("create lang by providing valid value") {
    CHECK_NOTHROW(Lang("en"));
    CHECK_NOTHROW(Lang("de"));
    CHECK_NOTHROW(Lang("fr"));
    CHECK_NOTHROW(Lang("it"));
    CHECK_NOTHROW(Lang("rm"));
    CHECK(Lang("de").value().length() > 0);
    CHECK(Lang("de").value() == "de");
    CHECK(Lang("de") == Lang("de"));
    CHECK(Lang("en") != Lang("de"));
  }

  SECTION("create lang by providing invalid value") {
    CHECK_THROWS_AS(Lang("sr"), xsd::Error);
  }

}


