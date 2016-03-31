#include <sstream>
#include "Statement.hpp"
#include "instructions.hpp"
#include "Register.hpp"
#include "StringLabel.hpp"


namespace
{
  std::string run_statements(std::vector<ProgramNode*>* statements)
  {
    std::stringstream s;
    for(auto &statement: *statements)
    {
      if (statement != nullptr)
        s << statement->gen_asm();
    }
    return s.str();
  }

  std::string run_else_ifs(std::vector<ElseIf*>* else_ifs, std::string jump_to_if_run)
  {
    std::stringstream s;
    for(auto &else_if: *else_ifs)
    {
      if (else_if != nullptr)
        s << else_if->gen_asm(jump_to_if_run);
    }
    return s.str();
  }

  std::string branch_to_on_false(Expression* expr, std::string branch_label, std::string note)
  {
    std::stringstream s;
    s << expr->gen_asm();
    s << MIPS::beq(expr->result(), MIPS::ZERO, branch_label, note);
    expr->release();
    return s.str();
  }

  std::string if_then_jump(Expression* expr,
                           std::vector<ProgramNode*>* statements,
                           std::string else_label,
                           std::string else_note,
                           std::string end_label,
                           std::string end_note)
  {
    std::stringstream s;
    s << branch_to_on_false(expr, else_label, else_note);
    s << run_statements(statements);
    s << MIPS::j(end_label, end_note);
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
  s << if_then_jump(expr, main_statements, else_label,"Testing an if statement's condition",
                                           end_label, "Finished the true branch of an if statement");

  if (optional_else_ifs != nullptr)
  {
    s << run_else_ifs(optional_else_ifs, end_label);
  }

  if (optional_else != nullptr)
  {
    s << run_statements(optional_else);
  }
  s << MIPS::label(end_label, "");

  return s.str();
}

std::string ElseIf::gen_asm(std::string end_label)
{
  auto else_label = StringLabel::get_unique_control_label();
  return if_then_jump(expr, statements, else_label, "Testing an else if's condition",
                                        end_label, "Finished running an else if");
}

std::string WhileStatement::gen_asm()
{
  std::stringstream s;
  auto start_while = StringLabel::get_unique_control_label();
  auto end_while = StringLabel::get_unique_control_label();
  s << MIPS::label(start_while,"");
  s << if_then_jump(expr, statements, end_while, "Testing whether to run this while loop",
                                      start_while, "Going back to start of the loop");
  return s.str();
}

std::string RepeatStatement::gen_asm()
{
  std::stringstream s;
  auto start_repeat = StringLabel::get_unique_control_label();
  auto end_repeat = StringLabel::get_unique_control_label();

  s << MIPS::label(start_repeat, "");
  s << run_statements(statements);
  s << branch_to_on_false(expr, start_repeat, "Testing whether to continue this repeat loop");
  s << MIPS::j(end_repeat, "Ending repeat loop");
  s << MIPS::label(end_repeat, "");

  return s.str();
}

std::string ForStatement::gen_asm()
{
  std::stringstream s;
  auto for_start = StringLabel::get_unique_control_label();
  auto for_end = StringLabel::get_unique_control_label();
  s << assignment->gen_asm();
  s << MIPS::label(for_start, "");
  s << branch_to_on_false(continue_condition, for_end, "Testing whether to continue: for loop");
  s << run_statements(statements);
  s << update->gen_asm();
  s << MIPS::j(for_start, "Going back to start of for loop");
  s << MIPS::label(for_end, "");
  s << reverse_update->gen_asm();
  return s.str();
}

std::string StopStatement::gen_asm()
{
  return MIPS::system_call(10);
}

std::string ReturnStatement::gen_asm()
{
  std::stringstream s;
  if(optional_return_value != nullptr)
  {
    s << optional_return_value->gen_asm();
    s << MIPS::move(MIPS::A0, optional_return_value->result(), "Loading a return a value");
    optional_return_value->release();
  }
  s << MIPS::jr(MIPS::RA, "Returning from function");
  return s.str();
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
