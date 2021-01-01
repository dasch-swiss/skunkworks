//
// Created by Ivan Subotic on 29/11/2020.
//

#include <string>
#include "catch2/catch.hpp"
#include "shared/xsd_types/xsd.h"
#include "shared/error/error.h"
#include "lang.h"

TEST_CASE("lang value type", "[admin][user][lang]") {

  using namespace std::string_literals; // enables s-suffix for std::string literals
  using namespace dsp;

  SECTION("create") {
    CHECK(Lang().empty());
    CHECK_NOTHROW(Lang("en"));
    CHECK_NOTHROW(Lang("de"));
    CHECK_NOTHROW(Lang("fr"));
    CHECK_NOTHROW(Lang("it"));
    CHECK_NOTHROW(Lang("rm"));
    CHECK(Lang("de").value().length() > 0);
    CHECK(Lang("de").value() == "de");
    CHECK(Lang(xsd::String("de"s)).value() == "de"s);
    CHECK(Lang(Lang("de")).value() == "de"s);
  }

  SECTION("direct assignments") {
    Lang lang;
    lang = "de"s;
    CHECK(lang.value() == "de"s);

    lang = Lang("fr");
    CHECK(lang.value() == "fr");
  }

  SECTION("restrictions") {
    CHECK_THROWS_AS(Lang("sr"s), xsd::Error);
  }

  SECTION("comparisons") {
    CHECK(Lang("de") == Lang("de"));
    CHECK(Lang("en") != Lang("de"));
  }

}


