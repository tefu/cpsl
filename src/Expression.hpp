#ifndef CPSL_EXPRESSION_H
#define CPSL_EXPRESSION_H
#include <string>
#include <vector>
#include "ProgramNode.hpp"

struct Expression : ProgramNode
{
  enum Type
  {
    BOOL,
    STRING,
    INTEGER,
    CHAR
  };
  virtual std::string gen_asm()=0;
  virtual bool is_constant() const=0;
  virtual Type data_type() const=0;
  virtual int result() const;
  virtual void allocate();
  virtual void release();
  static const int NULL_REGISTER = -1;
protected:
  int result_reg=NULL_REGISTER;
};

struct LogicalOr : Expression
{
  LogicalOr(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* left;
  const Expression* right;
};

struct LogicalAnd : Expression
{
  LogicalAnd(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* left;
  const Expression* right;
};

struct Equality : Expression
{
  Equality(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* left;
  const Expression* right;
};

struct Inequality : Expression
{
  Inequality(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* left;
  const Expression* right;
};

struct LessThanOrEqual : Expression
{
  LessThanOrEqual(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* left;
  const Expression* right;
};

struct LessThan : Expression
{
  LessThan(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* left;
  const Expression* right;
};


struct GreaterThanOrEqual : Expression
{
  GreaterThanOrEqual(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* left;
  const Expression* right;
};

struct GreaterThan : Expression
{
  GreaterThan(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* left;
  const Expression* right;
};

struct OperatorPlus : Expression
{
  OperatorPlus(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* left;
  const Expression* right;
};

struct OperatorMinus : Expression
{
  OperatorMinus(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* left;
  const Expression* right;
};

struct OperatorMult : Expression
{
  OperatorMult(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* left;
  const Expression* right;
};

struct OperatorDivide : Expression
{
  OperatorDivide(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* left;
  const Expression* right;
};

struct OperatorModulus : Expression
{
  OperatorModulus(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* left;
  const Expression* right;
};

struct Negation : Expression
{
  Negation(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* expr;
};

struct UnaryMinus : Expression
{
  UnaryMinus(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* expr;
};


struct FunctionCall : Expression
{
  FunctionCall(std::vector<Expression*>* el) : exprList(el) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const std::vector<Expression*>* exprList;
};


struct ToChar : Expression
{
  ToChar(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* expr;
};

struct ToInt : Expression
{
  ToInt(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* expr;
};

struct Predecessor : Expression
{
  Predecessor(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* expr;
};

struct Successor : Expression
{
  Successor(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const Expression* expr;
};

struct StringLiteral : Expression
{
  StringLiteral(std::string* l) : literal(l) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const std::string* literal;
};

struct CharLiteral : Expression
{
  CharLiteral(std::string* c) : literal(c) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const std::string* literal;
};

struct IntLiteral : Expression
{
  IntLiteral(int l) : literal(l) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const int literal;
};

struct BoolLiteral : Expression
{
  BoolLiteral(bool l) : literal(l) {}
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
  const bool literal;
};

struct LValue : Expression
{
  std::string gen_asm();
  bool is_constant() const;
  Type data_type() const;
};


#endif //CPSL_EXPRESSION_H
