#ifndef CPSL_LVALUE_HPP
#define CPSL_LVALUE_HPP
#include "Expression.hpp"

struct LValue
{
  virtual std::string assign(int result_register) = 0;
  virtual Expression* read()=0;
};

struct Variable: LValue
{
  Variable(std::shared_ptr<Type> t, int a) : type(t), address_offset(a) {}
  const std::shared_ptr<Type> type;
  const int address_offset;
  virtual std::string assign(int result_register);
  virtual Expression* read();
};

struct Constant: LValue
{
  Constant(Expression* e) : result(e) {}
  Expression* result;
  virtual std::string assign(int result_register);
  virtual Expression* read();
};


#endif //CPSL_LVALUE_HPP
