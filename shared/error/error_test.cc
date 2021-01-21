//
// Created by Lukas Rosenthaler on 21.01.21.
//

#include <iostream>

#include "catch2/catch.hpp"

#include "shared/error/error.h"

TEST_CASE("Agent", "Unit") {
  dsp::Error error(__FILE__, __LINE__, "Waseliwas", 5);
  CHECK(std::string(error.what()) == "Waseliwas");
}