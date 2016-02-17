#ifndef CPSL_SYMBOLTABLE_HPP
#define CPSL_SYMBOLTABLE_HPP
#include <string>
#include <map>
#include <memory>
#include "Expression.hpp"

struct Variable
{
  const Expression::Type type;
  const int address_offset;
  const bool is_constant;
};

namespace Symbol
{
  const int starting_address = 0;
  Expression::Type parse_type(std::string raw_type);
  int available_address_offset();
  std::shared_ptr<std::map<std::string, Variable>> get_table();
};

#endif //CPSL_SYMBOLTABLE_HPP
