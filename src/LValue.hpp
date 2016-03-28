#ifndef CPSL_LVALUE_HPP
#define CPSL_LVALUE_HPP
#include "Expression.hpp"

struct LValue
{
  virtual std::string assign(int result_register) = 0;
  virtual Type* get_type() = 0;
  virtual bool is_constant() = 0;
  virtual Expression* read()=0;
  virtual int size_on_stack();
};

struct GlobalVariable : LValue
{
  GlobalVariable(Type* t, int a) : type(t), address_offset(a) {}
  Type* type;
  const int address_offset;
  virtual std::string assign(int result_register);
  virtual Type* get_type();
  virtual bool is_constant();
  virtual Expression* read();
};

struct StackVariable : LValue
{
  StackVariable(Type* t, int a) : type(t), address_offset(a) {}
  Type* type;
  const int address_offset;
  virtual std::string assign(int result_register);
  virtual Type* get_type();
  virtual bool is_constant();
  virtual Expression* read();
  virtual int size_on_stack();
};

struct VarArgument : LValue
{
  VarArgument(Type* t, int a) : type(t), address_offset(a) {}
  Type* type;
  const int address_offset;
  virtual std::string assign(int result_register);
  virtual Type* get_type();
  virtual bool is_constant();
  virtual Expression* read();
};

struct RefArgument : LValue
{
  RefArgument(Type* t, int a) : type(t), address_offset(a) {}
  Type* type;
  const int address_offset;
  virtual std::string assign(int result_register);
  virtual Type* get_type();
  virtual bool is_constant();
  virtual Expression* read();
};


struct Constant: LValue
{
  Constant(Expression* e) : result(e) {}
  Expression* result;
  virtual std::string assign(int result_register);
  virtual Type* get_type();
  virtual bool is_constant();
  virtual Expression* read();
};


#endif //CPSL_LVALUE_HPP
