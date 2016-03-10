#ifndef CPSL_SYMBOLTABLE_HPP
#define CPSL_SYMBOLTABLE_HPP
#include <string>
#include <map>
#include <memory>
#include "Expression.hpp"
#include "LValue.hpp"

namespace Symbol
{
  void add_variable(std::string, std::string);
  void add_constant(std::string, Expression*);
  LValue* lookup(std::string);
  void push_table();
  void pop_table();
};

#endif //CPSL_SYMBOLTABLE_HPP
