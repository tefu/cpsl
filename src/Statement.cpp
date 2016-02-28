#include "Statement.hpp"
#include "instructions.hpp"
#include "Register.hpp"
#include <sstream>

std::string Assignment::gen_asm()
{
  std::stringstream s;
  s << expr->gen_asm();
  s << l_value->assign(expr->result());
  expr->release();
  return s.str();
}

std::string IfStatement::gen_asm()
{
  return "";
}

std::string WhileStatement::gen_asm()
{
  return "";
}

std::string RepeatStatement::gen_asm()
{
  return "";
}

std::string ForStatement::gen_asm()
{
  return "";
}

std::string StopStatement::gen_asm()
{
  return MIPS::system_call(10);
}

std::string ReturnStatement::gen_asm()
{
  return "";
}

std::string ReadStatement::gen_asm()
{
  std::stringstream s;
  for(auto &l_value: *l_value_list)
  {
    int result = Register::allocate_register();
    s << l_value->get_type()->read_in(result);
    s << l_value->assign(result);
    Register::release_register(result);
  }
  return s.str();
}

std::string WriteStatement::gen_asm()
{
  std::stringstream s;
  for (auto &expr: *exprList)
  {
    s << expr->gen_asm();
    s << expr->data_type()->write_out(expr->result());
    expr->release();
  }
  return s.str();
}

std::string ProcedureCall::gen_asm()
{
  return "";
}

std::string NullStatement::gen_asm()
{
  return "";
}
