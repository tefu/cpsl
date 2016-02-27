#include "Statement.hpp"
#include "instructions.hpp"
#include <sstream>

std::string Assignment::gen_asm()
{
  return "";
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
  return "";
}

std::string WriteStatement::gen_asm()
{
  std::stringstream s;
  for (auto &expr: *exprList)
  {
    s << expr->gen_asm();
    s << expr->data_type().write_out(expr->result());
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
