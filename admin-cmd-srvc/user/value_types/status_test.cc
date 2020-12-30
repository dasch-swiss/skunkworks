//
// Created by Ivan Subotic on 29/11/2020.
//

#include "catch2/catch.hpp"

#include "shared/xsd_types/xsd.h"

#include "status.h"

TEST_CASE("status value type", "[entities][user][status]") {

  using namespace admin::user;

  SECTION("create status") {
    CHECK_NOTHROW(Status());
  }

}


