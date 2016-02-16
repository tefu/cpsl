#include <iostream>
#include "instructions.hpp"

namespace
{
  std::string one_arg(std::string op_code, std::string a)
  {
    return op_code + " " + a + "\n";
  }

  std::string two_args(std::string op_code, std::string a, std::string b)
  {
    return op_code + " " + a + ", " + b + "\n";
  }

  std::string three_args(std::string op_code, std::string a, std::string b, std::string c)
  {
    return op_code + " " + a + ", " + b + ", " + c + "\n";
  }

  std::string stringify(int val)
  {
    std::stringstream s;
    s << val;
    return s.str();
  }

  std::string dress_up(int address)
  {
    return "$" + stringify(address);
  }


}


std::string MIPS::la(int dest, std::string address)
{
  return two_args("la", dress_up(dest), address);
}

std::string MIPS::li(int reg, int value)
{
  return two_args("li", dress_up(reg), stringify(value));
}

std::string MIPS::li(int reg, std::string character)
{
  return two_args("li", dress_up(reg), character);
}

std::string MIPS::add(int dest, int src, int value)
{
  return three_args("add",dress_up(dest), dress_up(src), stringify(value));
}

std::string MIPS::addi(int dest, int src, int to_add)
{
  return three_args("addi", dress_up(dest), dress_up(src), stringify(to_add));
}

std::string MIPS::beq(int dest, int src, std::string label) {
  return three_args("beq", dress_up(dest), dress_up(src), label);
}

std::string MIPS::bne(int dest, int src, std::string label) {
  return three_args("bne", dress_up(dest), dress_up(src), label);
}

std::string MIPS::blt(int dest, int src, std::string label) {
  return three_args("blt", dress_up(dest), dress_up(src), label);
}

std::string MIPS::bgt(int dest, int src, std::string label) {
  return three_args("bgt", dress_up(dest), dress_up(src), label);
}

std::string MIPS::branch(std::string label) {
  return one_arg("b", label);
}

std::string MIPS::store_word(int src, int offset, int dest)
{
  return two_args("sw", dress_up(src), stringify(offset) + "(" + dress_up(dest) + ")");
}

std::string MIPS::load_word(int dest, int offset, int src)
{
  return two_args("sw", dress_up(dest), stringify(offset) + "(" + dress_up(src) + ")");
}

std::string MIPS::data()
{
  return std::string(".data\n");
}
std::string MIPS::asciiz(std::string label, std::string ascii)
{
  std::stringstream s;
  s << label << ": " << ".asciiz " << ascii << "\n";
  return s.str();
}
std::string MIPS::text()
{
  return ".text\n";
}


std::string MIPS::push_on_stack(int reg)
{
  std::stringstream s;
  s << addi(SP, SP, -4)
    << store_word(reg, 0, SP);

  return s.str();
}

std::string MIPS::pop_off_stack(int reg)
{
  std::stringstream s;
  s << load_word(reg, 0, SP)
    << addi(SP, SP, 4);

  return s.str();
}

std::string MIPS::system_call(int call_number)
{
  std::stringstream s;
  s << li(V0, call_number)
    << "syscall\n";
  return s.str();
}


std::string MIPS::write_out(Expression::Type data_type, int register_location)
{
  std::stringstream s;

  s << add(A0, register_location, 0);
  switch (data_type)
  {
    case Expression::STRING:
      s << system_call(4);
      break;
    case Expression::CHAR:
      s << system_call(11);
      break;
    case Expression::INTEGER:
    case Expression::BOOL:
    default:
      s << system_call(1);
      break;
  }
  return s.str();
}



