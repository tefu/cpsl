#ifndef CPSL_PARSETREE_HPP
#define CPSL_PARSETREE_HPP
#include "Expression.hpp"
#include "Statement.hpp"
#include "Block.hpp"
#include "SymbolTable.hpp"
#include "Function.hpp"


namespace ParseTree {
  ProgramNode* program(std::vector<ProgramNode*>*, ProgramNode*);
  Block* block(std::vector<ProgramNode*>*);
  void VarDecl(std::vector<std::string>*, std::string*);
  void ConstDecl(std::string*, Expression*);
  std::vector<FormalParameter*>* formal_parameter(bool is_var, std::vector<std::string>*, std::string*);
  FunctionBlock* procedure_body(std::string* procedure_name, ProgramNode* body);
  FunctionBlock* function_body(std::string* procedure_name, ProgramNode* body);
  std::string* function_decl(std::string*,std::vector<FormalParameter*>*, std::shared_ptr<Type>);
  std::string* function_decl(std::string*,std::vector<FormalParameter*>*, std::string*);

  LogicalOr* logical_or(Expression*, Expression*);
  LogicalAnd* logical_and(Expression*, Expression*);
  Equality* equality(Expression*, Expression*);
  Inequality* inequality(Expression*, Expression*);
  LessThanOrEqual* less_than_or_equal(Expression*, Expression*);
  GreaterThanOrEqual* greater_than_or_equal(Expression*, Expression*);
  LessThan* less_than(Expression*, Expression*);
  GreaterThan* greater_than(Expression*, Expression*);
  OperatorPlus* plus(Expression*,Expression*);
  OperatorMinus* minus(Expression*, Expression*);
  OperatorMult* mult(Expression*, Expression*);
  OperatorDivide* divide(Expression*, Expression*);
  OperatorModulus* modulus(Expression*, Expression*);
  Negation* negation(Expression*);
  UnaryMinus* unary_minus(Expression*);
  FunctionCall* function_call(std::string*, std::vector<Expression*>*);
  ToChar* CHR(Expression*);
  ToInt* ORD(Expression*);
  Predecessor* PRED(Expression*);
  Successor* SUCC(Expression*);
  StringLiteral* string_literal(std::string*);
  CharLiteral* char_literal(std::string*);
  IntLiteral* integer_literal(int);
  LValue* l_value(std::string*);
  Assignment* assign(LValue*, Expression*);
  ReadStatement* read_statement(std::vector<LValue*>*);
  WriteStatement* write_statement(std::vector<Expression*>*);
  IfStatement* if_statement(Expression*,
                            std::vector<ProgramNode*>*,
                            std::vector<ElseIf*>*,
                            std::vector<ProgramNode*>*);
  ElseIf* else_if(Expression*, std::vector<ProgramNode*>*);
  WhileStatement* while_statement(Expression*,std::vector<ProgramNode*>*);
  RepeatStatement* repeat_statement(Expression*,std::vector<ProgramNode*>*);
  ForStatement* for_statement(LValue*, Expression*, bool, Expression*, std::vector<ProgramNode*>*);
  ReturnStatement* return_statement(Expression*);
  LValue* for_head(std::string*);
};


#endif //CPSL_PARSETREE_HPP
