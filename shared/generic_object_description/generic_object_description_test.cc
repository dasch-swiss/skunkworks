//
// Created by Lukas Rosenthaler on 05.01.21.
//
#include <memory>

#include "catch2/catch.hpp"

#include "shared/xsd_types/xsd_error.h"
#include "shared/error/error.h"
#include "generic_object_description.h"

TEST_CASE("Simple catch2 tests", "[catch2]") {
  CHECK_NOTHROW(dsp::GenericObjectDescription(1, "GAGA"));
  dsp::GenericObjectDescription gaga(1, "GAGA");
  gaga.member<xsd::String>("test-1", xsd::String("a test"));
  gaga.member<xsd::Integer>("test-2", xsd::Integer(42));
  CHECK(gaga.member<xsd::String>("test-1") == xsd::String("a test"));
  CHECK(gaga.member<xsd::Integer>("test-2") == xsd::Integer(42));
}