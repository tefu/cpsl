#ifndef CPSL_LVALUE_HPP
#define CPSL_LVALUE_HPP
#include "Expression.hpp"

struct LValue
{
  virtual std::string assign(int result_register) = 0;
  virtual std::shared_ptr<Type> get_type() = 0;
  virtual bool is_constant() = 0;
  virtual Expression* read()=0;
};

struct GlobalVariable : LValue
{
  GlobalVariable(std::shared_ptr<Type> t, int a) : type(t), address_offset(a) {}
  const std::shared_ptr<Type> type;
  const int address_offset;
  virtual std::string assign(int result_register);
  virtual std::shared_ptr<Type> get_type();
  virtual bool is_constant();
  virtual Expression* read();
};

struct Constant: LValue
{
  Constant(Expression* e) : result(e) {}
  Expression* result;
  virtual std::string assign(int result_register);
  virtual std::shared_ptr<Type> get_type();
  virtual bool is_constant();
  virtual Expression* read();
};


#endif //CPSL_LVALUE_HPP
