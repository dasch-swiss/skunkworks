//
// Created by Ivan Subotic on 29/11/2020.
//

#include "catch2/catch.hpp"

#include "shared/uuid.h"

#include "identifier.h"

TEST_CASE("identifier value type", "[entities][user][identifier]") {

  using namespace admin::user;

  SECTION("create identifier through default constructor (no provided value)") {
    CHECK_NOTHROW(Identifier());
    CHECK(Identifier().value().length() > 0);
  }

  SECTION("create identifier by providing existing value") {
    std::string existing_uuid = uuid::generate_uuid_v4();
    CHECK_NOTHROW(Identifier(existing_uuid));
    CHECK(Identifier(existing_uuid).value() == existing_uuid);
    CHECK(Identifier(existing_uuid) == Identifier(existing_uuid));
  }

}


