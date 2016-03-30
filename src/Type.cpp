#include "Type.hpp"
#include "instructions.hpp"
#include "Register.hpp"

namespace
{
  std::string write_with_call(int register_location, int call_number, std::string note)
  {
    std::stringstream s;
    s << MIPS::addi(MIPS::A0, register_location, 0, note);
    s << MIPS::system_call(call_number);
    return s.str();
  }

  std::string read_with_call(int register_location, int call_number, std::string note)
  {
    std::stringstream s;
    s << MIPS::system_call(call_number);
    s << MIPS::addi(register_location, MIPS::V0, 0, note);
    return s.str();
  }
}

int Type::word_size() const
{
  return 4;
}

bool Type::operator==(const Type& other_type)
{
  return type() == other_type.type();
}

bool Type::equals(const Array& other) const
{
  return false;
}

std::string Type::assign_to(int result_register, int address_offset, int address, std::string var_type)
{
  std::stringstream s;
  s << MIPS::store_word(result_register, address_offset, address, std::string("Assigning to a ") + var_type);
  return s.str();
}

Type* Type::subtype()
{
  return nullptr;
}

Expression* Type::find_index(Expression* user_index)
{
  return nullptr;
}


std::string Type::load_into(int target_register, int address_offset, int address, std::string var_type)
{
  std::stringstream s;
  s << MIPS::load_word(target_register, address_offset, address, std::string("Loading a ") + var_type);
  return s.str();
}

std::string Integer::write_out(int register_location) const {
  return write_with_call(register_location, 1, "Writing out an integer");
}

std::string Integer::read_in(int register_location) const
{
  return read_with_call(register_location, 5, "Reading in an integer");
}

std::string Integer::type() const {
  return integer_type();
}

std::string StringConstant::write_out(int register_location) const {
  return write_with_call(register_location, 4, "Writing out a string");
}

std::string StringConstant::read_in(int register_location) const
{
  return MIPS::error("cannot read in a string");
}

std::string StringConstant::type() const {
  return string_type();
}

std::string Character::write_out(int register_location) const {
  return write_with_call(register_location, 11, "Writing out a character");
}

std::string Character::read_in(int register_location) const
{
  return read_with_call(register_location, 12, "Reading in a character");
}

std::string Character::type() const {
  return char_type();
}

std::string Boolean::write_out(int register_location) const {
  std::stringstream s;
  s << MIPS::sne(register_location, register_location, MIPS::ZERO, "Flatten boolean to 0 or 1");
  s << write_with_call(register_location, 1, "Writing out a boolean");
  return s.str();
}

std::string Boolean::read_in(int register_location) const
{
  return MIPS::error("cannot read in a boolean");
}

std::string Boolean::type() const {
  return boolean_type();
}

std::string Null::write_out(int register_location) const {
  return MIPS::error("cannot write out a NULL type");
}

std::string Null::read_in(int register_location) const
{
  return MIPS::error("cannot read in a NULL type");
}

std::string Null::type() const {
  return null_type();
}


std::string Array::write_out(int) const
{
  return MIPS::error("Cannot write out an array.");
}

std::string Array::read_in(int register) const
{
  return MIPS::error("Cannot read in an array.");
}

std::string Array::type() const
{
  return array_type();
}

std::string Array::assign_to(int src_register, int address_offset, int dest_address, std::string var_type)
{
  std::stringstream s;
  int reg = Register::allocate_register();
  auto upper_copy_limit = word_size();
  for(int offset = 0; offset < upper_copy_limit; offset += ADDRESS_SIZE)
  {
    s << MIPS::load_word(reg, offset, src_register, "Grab array value");
    s << MIPS::store_word(reg, offset + address_offset, dest_address, "Store array value");
  }
  Register::release_register(reg);
  return s.str();
}

std::string Array::load_into(int target_register, int address_offset, int address, std::string var_type)
{
  return MIPS::addi(target_register, address, address_offset, std::string("Loading the address of a ") + var_type + " array.");
}

int Array::word_size() const
{
  return sub_type->word_size() * size;
}

bool Array::operator==(const Type& other)
{
  return other.equals(*this);
}

bool Array::equals(const Array &other) const
{
  return this->type() == other.type() && this->sub_type == other.sub_type;
}

Type* Array::subtype()
{
  return sub_type;
}

Expression* Array::find_index(Expression* user_index)
{
  auto offset = new OperatorMinus{user_index, new IntLiteral{index_offset}};
  return new OperatorMult{offset,new IntLiteral{subtype()->word_size()}};
}

std::string Record::write_out(int) const
{
  return "";
}

std::string Record::read_in(int register) const
{
  return "";
}

std::string Record::type() const
{
  return record_type();
}
