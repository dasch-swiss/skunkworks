#include "catch2/catch.hpp"

#include <memory>


#include "shared/xsd_types/xsd_error.h"
#include "shared/xsd_types/xsd_integer.h"


TEST_CASE("xsd integer type", "[catch2|") {

  SECTION("simple constructor") {
    CHECK_NOTHROW(xsd::Integer());
    CHECK_NOTHROW(xsd::Integer(42));
    xsd::Integer my_int(42);
    CHECK(static_cast<int64_t>(my_int) == 42);
    CHECK_NOTHROW(xsd::Integer("33"));
    CHECK_THROWS_AS(xsd::Integer("3F"), xsd::Error);
  }

  SECTION("simple constructor with restrictions") {
    std::shared_ptr<xsd::RestrictionMaxInclusive> restriction_max_inclusive = std::make_shared<xsd::RestrictionMaxInclusive>(10, "gaga");
    xsd::Integer my_int(restriction_max_inclusive);
    CHECK_THROWS_AS(my_int = 11, xsd::Error);
    CHECK(xsd::Integer(300) == xsd::Integer(300));
  }
}
