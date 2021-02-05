//
// Created by Lukas Rosenthaler on 30.12.20.
//

#include "catch2/catch.hpp"

#include <memory>

#include "shared/xsd_types/xsd.h"
#include "shared/error/error.h"

#include "shortcode.h"

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

