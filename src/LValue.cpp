#include "LValue.hpp"
#include "instructions.hpp"
#include "Register.hpp"

std::string Variable::assign(int result_register)
{
  std::stringstream s;
  s << MIPS::store_word(result_register, address_offset, MIPS::GP, "Assigning to a variable");
  return s.str();
}

std::shared_ptr<Type> Variable::get_type()
{
  return type;
}

bool Variable::is_constant()
{
  return false;
}

Expression* Variable::read()
{
  return new LoadExpression{type, address_offset};
}

std::string Constant::assign(int result_register)
{
  return MIPS::error("cannot assign to constant value");
}

std::shared_ptr<Type> Constant::get_type()
{
  return result->data_type();
}

bool Constant::is_constant()
{
  return true;
}

Expression* Constant::read()
{
  return result;
}
