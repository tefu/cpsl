#include "Type.hpp"
#include "instructions.hpp"

namespace
{
  std::string write_with_call(int register_location, int call_number, std::string note)
  {
    std::stringstream s;
    s << MIPS::addi(MIPS::A0, register_location, 0, note);
    s << MIPS::system_call(call_number);
    return s.str();
  }
}

std::string Integer::write_out(int register_location) {
  return write_with_call(register_location, 1, "Writing out an integer");
}

Type::Basic Integer::type() {
  return Basic::INTEGER;
}

std::string StringConstant::write_out(int register_location) {
  return write_with_call(register_location, 4, "Writing out a string");
}

Type::Basic StringConstant::type() {
  return Basic::STRING;
}

std::string Character::write_out(int register_location) {
  return write_with_call(register_location, 11, "Writing out a character");
}

Type::Basic Character::type() {
  return Basic::CHAR;
}

std::string Boolean::write_out(int register_location) {
  return write_with_call(register_location, 1, "Writing out a boolean");
}

Type::Basic Boolean::type() {
  return Basic::BOOL;
}
