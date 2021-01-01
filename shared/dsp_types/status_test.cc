//
// Created by Ivan Subotic on 29/11/2020.
//

#include "catch2/catch.hpp"

#include "shared/xsd_types/xsd.h"
#include "shared/error/error.h"
#include "status.h"

TEST_CASE("status value type", "[entities][user][status]") {

  using namespace dsp;

  SECTION("create") {
    CHECK(!Status().value());
    CHECK(Status(true).value());
    CHECK(Status(xsd::Boolean(true)).value());
    CHECK(Status(Status(true)).value());
    CHECK(Status("non_bool").value()); // anything is always true
  }

  SECTION("direct assignments") {
    Status status;
    CHECK(!status.value());
    status = true;
    CHECK(status.value());
  }

  SECTION("restrictions") {
    // FIXME: any kind of string is always true. Need to support more than two states.
    // CHECK_THROWS_AS(Status("non_bool"), xsd::Error);
  }

  SECTION("comparisons") {
    CHECK(Status() == Status());
  }

}
