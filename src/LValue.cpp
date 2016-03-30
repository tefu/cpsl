#include "LValue.hpp"
#include "instructions.hpp"
#include "Register.hpp"


int LValue::size_on_stack()
{
  return 0;
}

Type* LValue::get_subtype()
{
  return get_type()->subtype();
}

Expression* LValue::read()
{
  return read(address(), get_type());
}


/* Variables on the global space
 * ------------------------------------------------------------------------- */
std::string GlobalVariable::assign(int result_register)
{
  return get_type()->assign_to(result_register, address_offset, MIPS::GP, "global variable");
}

Type* GlobalVariable::get_type()
{
  return type;
}

bool GlobalVariable::is_constant()
{
  return false;
}

Expression* GlobalVariable::read(Expression* src_address, Type* expected_type)
{
  return new LoadExpression{expected_type, src_address};
}

Expression* GlobalVariable::address()
{
  return new Address{new IntLiteral{address_offset}, MIPS::GP};
}



/* Variables on the stack
 * ------------------------------------------------------------------------- */
std::string StackVariable::assign(int result_register)
{
  return get_type()->assign_to(result_register, address_offset, MIPS::SP, "stack variable");
}

Type* StackVariable::get_type()
{
  return type;
}

bool StackVariable::is_constant()
{
  return false;
}

Expression* StackVariable::read(Expression* src_address, Type* expected_type)
{
  return new LoadExpression{expected_type, src_address};
}

int StackVariable::size_on_stack()
{
  return get_type()->word_size();
}

Expression* StackVariable::address()
{
  return new Address{new IntLiteral{address_offset}, MIPS::SP};
}

/* Arguments
 * ------------------------------------------------------------------------- */
std::string VarArgument::assign(int result_register)
{
  return get_type()->assign_to(result_register, address_offset, MIPS::FP, "argument variable");
}

Type* VarArgument::get_type()
{
  return type;
}

bool VarArgument::is_constant()
{
  return false;
}

Expression*VarArgument::read(Expression* src_address, Type* expected_type)
{
  return new LoadExpression{expected_type, src_address};
}

Expression* VarArgument::address()
{
  return new Address{new IntLiteral{address_offset}, MIPS::FP};
}

std::string RefArgument::assign(int result_register)
{
  std::stringstream s;
  auto ref_address = Register::allocate_register();
  s << MIPS::load_word(ref_address, address_offset, MIPS::FP, "Loading a reference variable's address");
  s << get_type()->assign_to(result_register, 0, ref_address, "reference variable");

  Register::release_register(ref_address);
  return s.str();
}

Type* RefArgument::get_type()
{
  return type;
}

bool RefArgument::is_constant()
{
  return false;
}

Expression* RefArgument::read(Expression* src_address, Type* expected_type)
{
  return new RefExpression{expected_type, src_address};
}

Expression* RefArgument::address()
{
  return new Address{new IntLiteral{address_offset}, MIPS::FP};
}



/* Constants
 * ------------------------------------------------------------------------- */
std::string Constant::assign(int result_register)
{
  return MIPS::error("cannot assign to constant value");
}

Type* Constant::get_type()
{
  return result->data_type();
}

bool Constant::is_constant()
{
  return true;
}

Expression* Constant::read(Expression* src_address, Type* expected_type)
{
  return result;
}

Expression* Constant::address()
{
  return nullptr;
}

/* Array Access
 * ------------------------------------------------------------------------- */
std::string ArrayAccess::assign(int result_register)
{
  std::stringstream s;
  auto src_address = address();
  s << src_address->gen_asm();
  s << get_type()->assign_to(result_register, 0, src_address->result(), "array element");
  src_address->release();

  return s.str();
}

Type* ArrayAccess::get_type()
{
  return array->get_subtype();
}

bool ArrayAccess::is_constant()
{
  return false;
}

Expression* ArrayAccess::read(Expression* src_address, Type* expected_type)
{
  return array->read(src_address, expected_type);
}

Expression* ArrayAccess::address()
{
  auto correct_index = array->get_type()->find_index(index);
  return new OperatorPlus{correct_index, array->address()};
}
