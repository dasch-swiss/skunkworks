
#include "single_include/catch2/catch.hpp"

TEST_CASE("Simple catch2 tests", "[catch2|") {
  REQUIRE(1==1);
  REQUIRE_FALSE(2==3);
}
