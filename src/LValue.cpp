#include "LValue.hpp"
#include "instructions.hpp"
#include "Register.hpp"


int LValue::size_on_stack()
{
  return 0;
}

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

int StackVariable::size_on_stack()
{
  return get_type()->word_size();
}

/* Arguments
 * ------------------------------------------------------------------------- */
std::string VarArgument::assign(int result_register)
{
  std::stringstream s;
  s << MIPS::store_word(result_register, address_offset, MIPS::FP, "Assigning to an argument variable");
  return s.str();
}

std::shared_ptr<Type> VarArgument::get_type()
{
  return type;
}

bool VarArgument::is_constant()
{
  return false;
}

Expression*VarArgument::read()
{
  return new LoadExpression{type, address_offset, MIPS::FP};
}

std::string RefArgument::assign(int result_register)
{
  std::stringstream s;
  auto ref_address = Register::allocate_register();
  s << MIPS::load_word(ref_address, address_offset, MIPS::FP, "Loading a reference variable's address");
  s << MIPS::store_word(result_register, 0, ref_address, "Assigning to a reference variable");
  Register::release_register(ref_address);
  return s.str();
}

std::shared_ptr<Type> RefArgument::get_type()
{
  return type;
}

bool RefArgument::is_constant()
{
  return false;
}

Expression* RefArgument::read()
{
  return new RefExpression{type, address_offset, MIPS::FP};
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
