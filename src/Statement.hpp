#ifndef CPSL_STATEMENT_HPP
#define CPSL_STATEMENT_HPP
#include "ProgramNode.hpp"
#include "Expression.hpp"


struct Assignment : ProgramNode {
  std::string gen_asm();
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
  std::string gen_asm();
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
