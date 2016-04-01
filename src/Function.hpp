#ifndef CPSL_FUNCTION_HPP
#define CPSL_FUNCTION_HPP

#include <vector>
#include <memory>
#include "Type.hpp"
#include "StringLabel.hpp"
#include "Expression.hpp"
#include "FormalParameter.hpp"

struct Function
{
  Function(std::vector<FormalParameter*> params, Type* rt)
          : parameters(params),
            address(StringLabel::get_unique_function_label()),
            return_type(rt) {}
  std::vector<FormalParameter*> parameters;
  std::string address;
  Type* return_type;
  bool same_signature(const Function&);
  bool correct_types(std::vector<Type*>);
  bool correct_references(std::vector<Expression*>);

};

#endif //CPSL_FUNCTION_HPP
