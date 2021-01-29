//
// Created by Lukas Rosenthaler on 21.01.21.
//

#include <iostream>

#include "catch2/catch.hpp"

#include "shared/error/error.h"


TEST_CASE("Agent", "Unit") {
  dsp::Error error(__FILE__, __LINE__, "Waseliwas");
  CHECK_THAT(std::string(error.what()), Catch::Matchers::Contains("Msg: Waseliwas"));
  //dsp::Error error2 = MAKE_ERROR("aa={} bb={}", "gaga", 3.1415);
  //CHECK_THAT(std::string(error2.what()), Catch::Matchers::Contains("Msg: aa=gaga bb=3.1415"));
}