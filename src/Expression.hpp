#ifndef CPSL_EXPRESSION_H
#define CPSL_EXPRESSION_H
#include <string>
#include <vector>
#include <memory>
#include "ProgramNode.hpp"
#include "Type.hpp"

struct Expression : ProgramNode
{
  virtual std::string gen_asm()=0;
  virtual bool is_constant() const=0;
  virtual std::shared_ptr<Type> data_type() const=0;
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
  std::shared_ptr<Type> data_type() const;
  Expression* left;
  Expression* right;
};

struct LogicalAnd : Expression
{
  LogicalAnd(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  Expression* left;
  Expression* right;
};

struct Equality : Expression
{
  Equality(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  Expression* left;
  Expression* right;
};

struct Inequality : Expression
{
  Inequality(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  Expression* left;
  Expression* right;
};

struct LessThanOrEqual : Expression
{
  LessThanOrEqual(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  Expression* left;
  Expression* right;
};

struct LessThan : Expression
{
  LessThan(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  Expression* left;
  Expression* right;
};


struct GreaterThanOrEqual : Expression
{
  GreaterThanOrEqual(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  Expression* left;
  Expression* right;
};

struct GreaterThan : Expression
{
  GreaterThan(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  Expression* left;
  Expression* right;
};

struct OperatorPlus : Expression
{
  OperatorPlus(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  Expression* left;
  Expression* right;
};

struct OperatorMinus : Expression
{
  OperatorMinus(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  Expression* left;
  Expression* right;
};

struct OperatorMult : Expression
{
  OperatorMult(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  Expression* left;
  Expression* right;
};

struct OperatorDivide : Expression
{
  OperatorDivide(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  Expression* left;
  Expression* right;
};

struct OperatorModulus : Expression
{
  OperatorModulus(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  Expression* left;
  Expression* right;
};

struct Negation : Expression
{
  Negation(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  Expression* expr;
};

struct UnaryMinus : Expression
{
  UnaryMinus(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  Expression* expr;
};


struct FunctionCall : Expression
{
  FunctionCall(std::vector<Expression*>* el) : exprList(el) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  std::vector<Expression*>* exprList;
};


struct ToChar : Expression
{
  ToChar(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  virtual int result() const;
  virtual void release();
  Expression* expr;
};

struct ToInt : Expression
{
  ToInt(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  virtual int result() const;
  virtual void release();
  Expression* expr;
};

struct Predecessor : Expression
{
  Predecessor(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  Expression* expr;
};

struct Successor : Expression
{
  Successor(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  Expression* expr;
};

struct StringLiteral : Expression
{
  StringLiteral(std::string* l) : literal(l) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  std::string* literal;
};

struct CharLiteral : Expression
{
  CharLiteral(std::string* c) : literal(c) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  std::string* literal;
};

struct IntLiteral : Expression
{
  IntLiteral(int l) : literal(l) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  int literal;
};

struct BoolLiteral : Expression
{
  BoolLiteral(bool l) : literal(l) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
  bool literal;
};

struct LoadExpression : Expression
{
  LoadExpression(std::shared_ptr<Type> t, int a) : datatype(t), address_offset(a) {}
  std::string gen_asm();
  bool is_constant() const;
  std::shared_ptr<Type> data_type() const;
private:
  std::shared_ptr<Type> datatype;
  const int address_offset;

};


#endif //CPSL_EXPRESSION_H
