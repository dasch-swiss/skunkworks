//
// Created by Lukas Rosenthaler on 28.12.20.
//
#include "catch2/catch.hpp"

#include <memory>

#include "shared/xsd_types/xsd.h"
#include "shared/error/error.h"

#include "shortname.h"

TEST_CASE("DSP data types: Shortname", "Shortname") {
  CHECK_NOTHROW(dsp::Shortname("A_name"));
  CHECK_THROWS_AS(dsp::Shortname("a name that does not work"), xsd::Error);
  CHECK_THROWS_AS(dsp::Shortname("4name"), xsd::Error);
  CHECK_THROWS_AS(dsp::Shortname("XXXXXXXXXX_XXXXXXXXXX_XXXXXXXXXX_XXXXXXXXXX_XXXXXXXXXX_XXXXXXXXXX_"), xsd::Error);
  dsp::Shortname a("MyName");
  CHECK(a == "MyName");
  CHECK("MyName" == static_cast<std::string>(a));
  CHECK("MyName" == (std::string) a);
  std::string str = static_cast<std::string>(a);
  dsp::Shortname b("MyName");
  CHECK(a == b);
  xsd::String ss("MyName");
  CHECK(a == ss);
  dsp::Shortname c;
  CHECK_THROWS_AS(c  = "0name", xsd::Error);
}
