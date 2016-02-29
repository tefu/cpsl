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

struct ElseIf {
    ElseIf(Expression* e, std::vector<ProgramNode*>* s) :
            expr(e), statements(s) {}
    Expression* expr;
    std::string gen_asm(std::string end_label);
    std::vector<ProgramNode*>* statements;
};

struct IfStatement : ProgramNode {
  IfStatement(Expression* e,
              std::vector<ProgramNode*>* m,
              std::vector<ElseIf*>* oei,
              std::vector<ProgramNode*>* oe) :
    expr(e), main_statements(m), optional_else_ifs(oei), optional_else(oe) {}
  std::string gen_asm();
  Expression* expr;
  std::vector<ProgramNode*>* main_statements;
  std::vector<ElseIf*>* optional_else_ifs;
  std::vector<ProgramNode*>* optional_else;
};

struct WhileStatement : ProgramNode {
  WhileStatement(Expression* e, std::vector<ProgramNode*>* s) :
          expr(e), statements(s) {}
  std::string gen_asm();
  Expression* expr;
  std::vector<ProgramNode*>* statements;
};

struct RepeatStatement : ProgramNode {
  RepeatStatement(Expression* e, std::vector<ProgramNode*>* s) :
          expr(e), statements(s) {}
  std::string gen_asm();
  Expression* expr;
  std::vector<ProgramNode*>* statements;
};

struct ForStatement : ProgramNode {
  ForStatement(Assignment* a, Expression* c, std::vector<ProgramNode*>* s, ProgramNode* u) :
          assignment(a), continue_condition(c), statements(s), update(u) {}
  Assignment* assignment;
  Expression* continue_condition;
  std::vector<ProgramNode*>* statements;
  ProgramNode* update;
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
