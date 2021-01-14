//
// Created by Ivan Subotic on 29/11/2020.
//

#include <string>
#include <memory>
#include <unordered_map>

#include "catch2/catch.hpp"

//#include "shared/uuid.h"
#define UUID_SYSTEM_GENERATOR

#include "external/stduuid/gsl/gsl" // compiles but does not work in IDE
#include "gsl/gsl" // only needed for IDE
#include "external/stduuid/include/uuid.h" // compiles but does not work in IDE
#include "include/uuid.h" // only needed for IDE

#include "identifier.h"

using namespace std::string_literals;

TEST_CASE("identifier value type", "[entities][user][identifier]") {

  using namespace dsp;

  SECTION("create identifier through default constructor (no provided value)") {
    CHECK_NOTHROW(Identifier());
    CHECK(Identifier().to_string().length() > 0);
  }

  SECTION("create identifier by providing existing value") {
    std::string existing_uuid = uuids::to_string(uuids::uuid_system_generator{}());
    CHECK_NOTHROW(Identifier(existing_uuid));
    CHECK(Identifier(existing_uuid).to_string() == existing_uuid);
    CHECK(Identifier(existing_uuid) == Identifier(existing_uuid));
  }

  SECTION("Named identifiers") {
    dsp::Identifier named1("GAGA", "gugus");
    dsp::Identifier named2("GAGA", "gugus2");
    CHECK(named1 != named2);
  }

}


