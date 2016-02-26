#include <iostream>
#include "catch.hpp"
#include "Type.hpp"

TEST_CASE("Types work")
{
  Integer a{};
  Integer b{};
  Boolean c{};

  REQUIRE(a.type() == b.type());
  REQUIRE(a.type() != c.type());

}