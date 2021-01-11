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

  SECTION("other") {
    CHECK_NOTHROW(dsp::Identifier());
    std::unordered_map<dsp::Identifier, std::string> mm;
    dsp::Identifier id1;
    dsp::Identifier id2;
    mm[id1] = "eins"s;
    mm[id2] = "zwei"s;
    CHECK(mm[id1] == "eins"s);
    dsp::Identifier my_id;
    std::string my_id_string = my_id.to_string();
    dsp::Identifier my_id2(my_id_string);
    CHECK(my_id == my_id2);
    auto named_id1 = dsp::Identifier("dasch.swiss"s, "lukas"s);
    auto named_id2 = dsp::Identifier("dasch.swiss"s, "lukas"s);
    CHECK(named_id1 == named_id2);
  }

}


