#include "catch.hpp"
#include "instructions.hpp"

TEST_CASE("Push pushes a register", "[MIPS::push_on_stack]")
{
  REQUIRE(MIPS::push_on_stack("s0") == "addi $sp, $sp, -4\nsw $s0, 0($sp)\n");
  REQUIRE(MIPS::pop_off_stack("s0") == "lw $s0, 0($sp)\naddi $sp, $sp, 4\n");

  std::string print_string_result = ".data\nstring: .asciiz \"Sup, world\"\n.text.\nla $a0, string\n" + MIPS::system_call(4);
  REQUIRE(MIPS::print_string("\"Sup, world\"") == print_string_result);
  REQUIRE(MIPS::print_int(34) == "add $a0, 34, 0\nsys(1)\n");

  REQUIRE(MIPS::system_call(4) == "li $v0, 4\nsyscall\n");

}