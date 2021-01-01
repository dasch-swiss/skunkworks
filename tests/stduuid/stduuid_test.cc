//
// Created by Ivan Subotic on 29/12/2020.
//

#include "catch2/catch.hpp"

#include "external/stduuid/gsl/gsl" // compiles but does not work in IDE
#include "gsl/gsl" // only needed for IDE
#include "external/stduuid/include/uuid.h" // compiles but does not work in IDE
#include "include/uuid.h" // only needed for IDE

TEST_CASE("stduuid tests", "[stduuid|") {
  uuids::uuid empty;
  CHECK(empty.is_nil());

  uuids::uuid_name_generator gen(uuids::uuid::from_string("47183823-2574-4bfd-b411-99ed177d3e43").value());
  uuids::uuid const id = gen("john");

  CHECK(!id.is_nil());
  CHECK(id.version() == uuids::uuid_version::name_based_sha1);
  CHECK(id.variant() == uuids::uuid_variant::rfc);
}