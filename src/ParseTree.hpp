#ifndef CPSL_PARSETREE_HPP
#define CPSL_PARSETREE_HPP
#include "Expression.hpp"
#include "Statement.hpp"
#include "Block.hpp"


namespace ParseTree {
  ProgramNode* program(ProgramNode*);
  Block* block(std::vector<ProgramNode*>*);
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
  FunctionCall* function_call(std::vector<Expression*>*);
  ToChar* CHR(Expression*);
  ToInt* ORD(Expression*);
  Predecessor* PRED(Expression*);
  Successor* SUCC(Expression*);
  StringLiteral* string_literal(std::string*);
  CharLiteral* char_literal(std::string*);
  IntLiteral* integer_literal(int);
  LValue* l_value();
};


#endif //CPSL_PARSETREE_HPP