#ifndef CPSL_LVALUE_HPP
#define CPSL_LVALUE_HPP
#include "Expression.hpp"

struct LValue
{
  virtual std::string assign(int result_register) = 0;
  virtual Type* get_type() = 0;
  virtual bool is_constant() = 0;
  virtual Expression* read(Expression*, Type*)=0;
  virtual Expression* address()=0;
  virtual Expression* read();
  virtual Type* get_subtype();
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
  virtual Expression* read(Expression*, Type*);
  virtual Expression* address();
};

struct StackVariable : LValue
{
  StackVariable(Type* t, int a) : type(t), address_offset(a) {}
  Type* type;
  const int address_offset;
  virtual std::string assign(int result_register);
  virtual Type* get_type();
  virtual bool is_constant();
  virtual Expression* read(Expression*, Type*);
  virtual int size_on_stack();
  virtual Expression* address();
};

struct VarArgument : LValue
{
  VarArgument(Type* t, int a) : type(t), address_offset(a) {}
  Type* type;
  const int address_offset;
  virtual std::string assign(int result_register);
  virtual Type* get_type();
  virtual bool is_constant();
  virtual Expression* read(Expression*, Type*);
  virtual Expression* address();
};

struct RefArgument : LValue
{
  RefArgument(Type* t, int a) : type(t), address_offset(a) {}
  Type* type;
  const int address_offset;
  virtual std::string assign(int result_register);
  virtual Type* get_type();
  virtual bool is_constant();
  virtual Expression* read(Expression*, Type*);
  virtual Expression* address();
};


struct Constant: LValue
{
  Constant(Expression* e) : result(e) {}
  Expression* result;
  virtual std::string assign(int result_register);
  virtual Type* get_type();
  virtual bool is_constant();
  virtual Expression* read(Expression*, Type*);
  virtual Expression* address();
};

struct ArrayAccess : LValue
{
  ArrayAccess(LValue* lval, Expression* e)
    : array(lval), index(e) {}
  virtual std::string assign(int result_register);
  virtual Type* get_type();
  virtual bool is_constant();
  virtual Expression* read(Expression*, Type*);
  virtual Expression* address();
  LValue* array;
  Expression* index;
};

#endif //CPSL_LVALUE_HPP
