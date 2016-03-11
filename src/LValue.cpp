#include "LValue.hpp"
#include "instructions.hpp"
#include "Register.hpp"


/* Variables on the global space
 * ------------------------------------------------------------------------- */
std::string GlobalVariable::assign(int result_register)
{
  std::stringstream s;
  s << MIPS::store_word(result_register, address_offset, MIPS::GP, "Assigning to a variable");
  return s.str();
}

std::shared_ptr<Type> GlobalVariable::get_type()
{
  return type;
}

bool GlobalVariable::is_constant()
{
  return false;
}

Expression* GlobalVariable::read()
{
  return new LoadExpression{type, address_offset, MIPS::GP};
}


/* Variables on the stack
 * ------------------------------------------------------------------------- */
std::string StackVariable::assign(int result_register)
{
  std::stringstream s;
  s << MIPS::store_word(result_register, address_offset, MIPS::SP, "Assigning to a stack variable");
  return s.str();
}

std::shared_ptr<Type> StackVariable::get_type()
{
  return type;
}

bool StackVariable::is_constant()
{
  return false;
}

Expression* StackVariable::read()
{
  return new LoadExpression{type, address_offset, MIPS::SP};
}

/* Arguments
 * ------------------------------------------------------------------------- */
std::string ArgumentVariable::assign(int result_register)
{
  std::stringstream s;
  s << MIPS::store_word(result_register, address_offset, MIPS::FP, "Assigning to an argument variable");
  return s.str();
}

std::shared_ptr<Type> ArgumentVariable::get_type()
{
  return type;
}

bool ArgumentVariable::is_constant()
{
  return false;
}

Expression* ArgumentVariable::read()
{
  return new LoadExpression{type, address_offset, MIPS::FP};
}


/* Constants
 * ------------------------------------------------------------------------- */
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
