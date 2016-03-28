#ifndef CPSL_FORMALPARAMETER_HPP
#define CPSL_FORMALPARAMETER_HPP
#include <string>
#include <memory>
#include "Type.hpp"

struct FormalParameter
{
  FormalParameter(bool iv, std::string arg, Type* t)
          : is_variable(iv), argument(arg), type(t) {}
  bool is_variable;
  std::string argument;
  Type* type;
  bool operator==(const FormalParameter&);
};

#endif //CPSL_FORMALPARAMETER_HPP
