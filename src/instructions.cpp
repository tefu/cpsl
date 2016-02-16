#include <iostream>
#include "instructions.hpp"

namespace
{
  std::string comment(std::string note)
  {
    std::stringstream s;
    if(note != "")
      s << " # " << note;
    s << "\n";
    return s.str();
  }
  std::string one_arg(std::string op_code, std::string a, std::string note)
  {
    return op_code + " " + a + comment(note);
  }

  std::string two_args(std::string op_code, std::string a, std::string b, std::string note)
  {
    return op_code + " " + a + ", " + b + comment(note);
  }

  std::string three_args(std::string op_code, std::string a, std::string b, std::string c, std::string note)
  {
    return op_code + " " + a + ", " + b + ", " + c + comment(note);
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


std::string MIPS::la(int dest, std::string address, std::string note)
{
  return two_args("la", dress_up(dest), address, note);
}

std::string MIPS::li(int reg, int value, std::string note)
{
  return two_args("li", dress_up(reg), stringify(value), note);
}

std::string MIPS::li(int reg, std::string character, std::string note)
{
  return two_args("li", dress_up(reg), character, note);
}

std::string MIPS::add(int dest, int src, int value, std::string note)
{
  return three_args("add",dress_up(dest), dress_up(src), stringify(value), note);
}

std::string MIPS::addi(int dest, int src, int to_add, std::string note)
{
  return three_args("addi", dress_up(dest), dress_up(src), stringify(to_add), note);
}

std::string MIPS::beq(int dest, int src, std::string label, std::string note) {
  return three_args("beq", dress_up(dest), dress_up(src), label, note);
}

std::string MIPS::bne(int dest, int src, std::string label, std::string note) {
  return three_args("bne", dress_up(dest), dress_up(src), label, note);
}

std::string MIPS::blt(int dest, int src, std::string label, std::string note) {
  return three_args("blt", dress_up(dest), dress_up(src), label, note);
}

std::string MIPS::bgt(int dest, int src, std::string label, std::string note) {
  return three_args("bgt", dress_up(dest), dress_up(src), label, note);
}

std::string MIPS::logical_or(int dest, int src1, int src2, std::string note) {
  return three_args("or", dress_up(dest), dress_up(src1), dress_up(src2), note);
}

std::string MIPS::logical_and(int dest, int src1, int src2, std::string note) {
  return three_args("and", dress_up(dest), dress_up(src1), dress_up(src2), note);
}


std::string MIPS::branch(std::string label, std::string note) {
  return one_arg("b", label, note);
}

std::string MIPS::store_word(int src, int offset, int dest, std::string note)
{
  return two_args("sw", dress_up(src), stringify(offset) + "(" + dress_up(dest) + ")", note);
}

std::string MIPS::load_word(int dest, int offset, int src, std::string note)
{
  return two_args("sw", dress_up(dest), stringify(offset) + "(" + dress_up(src) + ")", note);
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
  s << addi(SP, SP, -4, "Decrement stack counter")
    << store_word(reg, 0, SP, "Store value on stack");

  return s.str();
}

std::string MIPS::pop_off_stack(int reg)
{
  std::stringstream s;
  s << load_word(reg, 0, SP, "Take value off of stack")
    << addi(SP, SP, 4, "Increment stack counter");

  return s.str();
}

std::string MIPS::system_call(int call_number)
{
  std::stringstream s;
  s << li(V0, call_number, "")
    << "syscall\n";
  return s.str();
}


std::string MIPS::write_out(Expression::Type data_type, int register_location)
{
  std::stringstream s;

  s << add(A0, register_location, 0, "Writing out data");
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
