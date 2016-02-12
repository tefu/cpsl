#include "instructions.hpp"


std::string MIPS::push_on_stack(std::string reg)
{
  std::stringstream s;
  s << "addi $sp, $sp, -4\n" <<
       "sw $" << reg << ", 0($sp)\n";

  return s.str();
}

std::string MIPS::pop_off_stack(std::string reg)
{
  std::stringstream s;
  s << "lw $" << reg << ", 0($sp)\naddi $sp, $sp, 4\n";
  return s.str();
}

std::string MIPS::system_call(int call_number)
{
  std::stringstream s;
  s << "li $v0, " << call_number << "\n" << "syscall\n";
  return s.str();
}

std::string MIPS::print_string(std::string user_string)
{

  std::stringstream s;
  s << ".data\nstring: .asciiz " << user_string << "\n.text.\nla $a0, string\n" + MIPS::system_call(4);
  return s.str();
}


std::string MIPS::print_int(int number)
{
  std::stringstream s;
  s << "add $a0, " << number << ", 0\nsys(1)\n";
  return s.str();
}
