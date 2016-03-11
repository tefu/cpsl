#ifndef CPSL_SYMBOLTABLE_HPP
#define CPSL_SYMBOLTABLE_HPP
#include <string>
#include <map>
#include <memory>
#include "Expression.hpp"
#include "LValue.hpp"
#include "Function.hpp"

namespace Symbol
{
  void add_variable(std::string, std::shared_ptr<Type>);
  void add_argument(std::string, std::shared_ptr<Type>);
  void add_constant(std::string, Expression*);
  void add_function(std::string, std::shared_ptr<Function>);
  LValue* lookup(std::string);
  std::shared_ptr<Type> lookup_type(std::string);
  std::shared_ptr<Function> lookup_function(std::string);
  void push_table();
  void pop_table();
  int size_of_last_table_vars();
};

#endif //CPSL_SYMBOLTABLE_HPP
