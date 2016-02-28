#ifndef CPSL_STATEMENT_HPP
#define CPSL_STATEMENT_HPP
#include "ProgramNode.hpp"
#include "Expression.hpp"
#include "LValue.hpp"


struct Assignment : ProgramNode {
  Assignment(LValue* l, Expression* e) : l_value(l), expr(e) {}
  std::string gen_asm();
  LValue* l_value;
  Expression* expr;
};

struct IfStatement : ProgramNode {
  std::string gen_asm();
};

struct WhileStatement : ProgramNode {
  std::string gen_asm();
};

struct RepeatStatement : ProgramNode {
  std::string gen_asm();
};

struct ForStatement : ProgramNode {
  std::string gen_asm();
};

struct StopStatement : ProgramNode {
  StopStatement(){}
  std::string gen_asm();
};

struct ReturnStatement : ProgramNode {
  std::string gen_asm();
};

struct ReadStatement : ProgramNode {
  ReadStatement(std::vector<LValue*>* ll) : l_value_list(ll) {}
  std::string gen_asm();
  std::vector<LValue*>* l_value_list;
};

struct WriteStatement : ProgramNode {
  WriteStatement(std::vector<Expression*>* el) : exprList(el) {}
  std::string gen_asm();
  const std::vector<Expression*>* exprList;
};

struct ProcedureCall: ProgramNode {
  std::string gen_asm();
};

struct NullStatement: ProgramNode {
  std::string gen_asm();
};
#endif //CPSL_STATEMENT_HPP
