//
// Created by Lukas Rosenthaler on 18.12.20.
//

#include "catch2/catch.hpp"
#include "base_value.h"
#include "simple_text_value.h"

TEST_CASE("Simple catch2 tests", "[catch2|") {

//SimpleTextValue text_value;

REQUIRE(1==1);
REQUIRE_FALSE(2==3);
}

