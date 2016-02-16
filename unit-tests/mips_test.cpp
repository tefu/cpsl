#include <iostream>
#include "catch.hpp"
#include "instructions.hpp"

TEST_CASE("Push pushes a register", "[MIPS::push_on_stack]")
{

  std::cout << MIPS::addi(8, MIPS::V0, -48);
  std::cout << MIPS::bne(8, 33, "main");
  std::cout << MIPS::branch("main");
  std::cout << MIPS::add(9, 10, 100);

}