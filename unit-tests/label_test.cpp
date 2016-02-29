#include <iostream>
#include "StringLabel.hpp"
#include "catch.hpp"

TEST_CASE("Address labels are formed properly")
{
  auto string = StringLabel::get_unique_string_label();
  auto string2 = StringLabel::get_unique_string_label();
  auto branch = StringLabel::get_unique_control_label();
  auto branch2 = StringLabel::get_unique_control_label();

  REQUIRE(string.compare("string_0") == 0);
  REQUIRE(branch.compare("branch_0") == 0);
  REQUIRE(string2.compare("string_1") == 0);
  REQUIRE(branch2.compare("branch_1") == 0);
}