#ifndef CPSL_EXPRESSION_H
#define CPSL_EXPRESSION_H
#include <string>
#include <vector>
#include <memory>
#include "ProgramNode.hpp"
#include "Type.hpp"
#include "FormalParameter.hpp"

struct Expression : ProgramNode
{
  virtual std::string gen_asm()=0;
  virtual bool is_constant() const=0;
  virtual Type* data_type() const=0;
  virtual int result() const;
  virtual int flatten_int() const;
  virtual void allocate();
  virtual void release();
  virtual bool can_be_referenced();
  virtual std::string get_address();
  static const int NULL_REGISTER = -1;
protected:
  int result_reg=NULL_REGISTER;
};

struct LogicalOr : Expression
{
  LogicalOr(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  Expression* left;
  Expression* right;
};

struct LogicalAnd : Expression
{
  LogicalAnd(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  Expression* left;
  Expression* right;
};

struct Equality : Expression
{
  Equality(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  Expression* left;
  Expression* right;
};

struct Inequality : Expression
{
  Inequality(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  Expression* left;
  Expression* right;
};

struct LessThanOrEqual : Expression
{
  LessThanOrEqual(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  Expression* left;
  Expression* right;
};

struct LessThan : Expression
{
  LessThan(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  Expression* left;
  Expression* right;
};


struct GreaterThanOrEqual : Expression
{
  GreaterThanOrEqual(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  Expression* left;
  Expression* right;
};

struct GreaterThan : Expression
{
  GreaterThan(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  Expression* left;
  Expression* right;
};

struct OperatorPlus : Expression
{
  OperatorPlus(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  int flatten_int() const;
  Expression* left;
  Expression* right;
};

struct OperatorMinus : Expression
{
  OperatorMinus(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  int flatten_int() const;
  Expression* left;
  Expression* right;
};

struct OperatorMult : Expression
{
  OperatorMult(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  int flatten_int() const;
  Expression* left;
  Expression* right;
};

struct OperatorDivide : Expression
{
  OperatorDivide(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  int flatten_int() const;
  Expression* left;
  Expression* right;
};

struct OperatorModulus : Expression
{
  OperatorModulus(Expression* l, Expression* r) : left(l), right(r) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  int flatten_int() const;
  Expression* left;
  Expression* right;
};

struct Negation : Expression
{
  Negation(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  int flatten_int() const;
  Expression* expr;
};

struct UnaryMinus : Expression
{
  UnaryMinus(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  int flatten_int() const;
  Expression* expr;
};


struct FunctionCall : Expression
{
  FunctionCall(std::vector<FormalParameter*> fparams,
               std::vector<Expression*> el,
               Type* rt,
               std::string jt,
               int sov)
    : parameters(fparams), exprList(el), return_type(rt), jump_to(jt), size_of_vars(sov) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  std::vector<FormalParameter*> parameters;
  std::vector<Expression*> exprList;
  Type* return_type;
  std::string jump_to;
  const int size_of_vars;
};


struct ToChar : Expression
{
  ToChar(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  virtual int result() const;
  virtual void release();
  Expression* expr;
};

struct ToInt : Expression
{
  ToInt(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  virtual int result() const;
  virtual void release();
  Expression* expr;
};

struct Predecessor : Expression
{
  Predecessor(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  Expression* expr;
};

struct Successor : Expression
{
  Successor(Expression* e) : expr(e) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  Expression* expr;
};

struct StringLiteral : Expression
{
  StringLiteral(std::string* l) : literal(l) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  std::string* literal;
};

struct CharLiteral : Expression
{
  CharLiteral(std::string* c) : literal(c) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  std::string* literal;
};

struct IntLiteral : Expression
{
  IntLiteral(int l) : literal(l) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  int flatten_int() const;
  int literal;
};

struct BoolLiteral : Expression
{
  BoolLiteral(bool l) : literal(l) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  bool literal;
};

struct LoadExpression : Expression
{
  LoadExpression(Type* t, Expression* a) : datatype(t), address(a) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  bool can_be_referenced();
  std::string get_address();
  Expression* address;
private:
  Type* datatype;
};

struct Address : Expression
{
  Address(Expression* o, int sr) : offset(o), starting_register(sr) {}
  std::string gen_asm();
  bool is_constant() const;
  Type* data_type() const;
  Expression* offset;
  int starting_register;
};

#endif //CPSL_EXPRESSION_H
