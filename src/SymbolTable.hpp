#ifndef CPSL_SYMBOLTABLE_HPP
#define CPSL_SYMBOLTABLE_HPP
#include <string>
#include <map>
#include <memory>
#include "Expression.hpp"

struct Variable
{
  Variable(std::shared_ptr<Type> t, int a) : type(t), address_offset(a) {}
  const std::shared_ptr<Type> type;
  const int address_offset;
};

struct Constant
{
  Constant(Expression* e) : result(e) {}
  const Expression* result;
};

namespace Symbol
{
  void add_variable(std::string, std::string);
  void add_constant(std::string, Expression*);
  std::shared_ptr<Variable> lookup_variable(std::string);
  std::shared_ptr<Constant> lookup_constant(std::string);

};

#endif //CPSL_SYMBOLTABLE_HPP
