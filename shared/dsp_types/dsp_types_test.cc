//
// Created by Lukas Rosenthaler on 28.12.20.
//

#include "catch2/catch.hpp"

#include <memory>

#include "helpers/xsd_types/xsd.h"
#include "helpers/error.h"

#include "shortcode.h"
#include "shortname.h"

TEST_CASE("DSP data type: Shortcode", "Shortcode") {
  CHECK_NOTHROW(dsp::Shortcode("4123"));
  CHECK_THROWS_AS(dsp::Shortcode("412X"), xsd::Error);
  CHECK_THROWS_AS(dsp::Shortcode("412"), xsd::Error);
  CHECK_THROWS_AS(dsp::Shortcode("41234"), xsd::Error);
  dsp::Shortcode a("4123");
  CHECK(a == "4123");
  CHECK("4123" == static_cast<std::string>(a));
  CHECK("4123" == (std::string) a);
  std::string str = static_cast<std::string>(a);
  dsp::Shortcode b("4123");
  CHECK(a == b);
  xsd::String ss("4123");
  CHECK(a == ss);
  dsp::Shortcode c;
  CHECK_THROWS_AS(c  = "X234", xsd::Error);
}

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
