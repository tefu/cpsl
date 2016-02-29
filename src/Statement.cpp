#include <sstream>
#include "Statement.hpp"
#include "instructions.hpp"
#include "Register.hpp"
#include "StringLabel.hpp"


namespace
{
  std::string if_then_jump(Expression* expr,
                           std::string else_label,
                           std::string end_label,
                           std::vector<ProgramNode*>* statements)
  {
    std::stringstream s;
    s << expr->gen_asm();
    s << MIPS::beq(expr->result(), MIPS::ZERO, else_label, "Testing an if statement's condition");
    expr->release();
    for(auto &statement: *statements)
    {
      if (statement != nullptr)
        s << statement->gen_asm();
    }
    s << MIPS::j(end_label, "Finished the true branch of an if statement");
    s << MIPS::label(else_label, "");
    return s.str();
  }
}

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
  std::stringstream s;
  auto else_label = StringLabel::get_unique_control_label();
  auto end_label = StringLabel::get_unique_control_label();
  s << if_then_jump(expr, else_label, end_label, main_statements);

  if (optional_else_ifs != nullptr)
  {
    for (auto &elseif: *optional_else_ifs)
    {
      if (elseif != nullptr)
        s << elseif->gen_asm(end_label);
    }
  }

  if (optional_else != nullptr)
  {
    for (auto &statement: *optional_else)
    {
      if (statement != nullptr)
        s << statement->gen_asm();
    }
  }
  s << MIPS::label(end_label, "");

  return s.str();
}

std::string ElseIf::gen_asm(std::string end_label)
{
  auto else_label = StringLabel::get_unique_control_label();
  return if_then_jump(expr, else_label, end_label, statements);
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
