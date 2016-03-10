#ifndef CPSL_FUNCTION_HPP
#define CPSL_FUNCTION_HPP

#include <vector>
#include <memory>
#include "Type.hpp"
#include "StringLabel.hpp"

struct FormalParameter
{
  FormalParameter(bool iv, std::vector<std::string> args, std::shared_ptr<Type> t)
          : is_variable(iv), arguments(args), type(t) {}
  bool is_variable;
  std::vector<std::string> arguments;
  std::shared_ptr<Type> type;
  bool operator==(const FormalParameter&);
};


struct Function
{
  Function(std::vector<FormalParameter*> params, std::shared_ptr<Type> rt)
          : parameters(params),
            address(StringLabel::get_unique_function_label()),
            return_type(rt) {}
  std::vector<FormalParameter*> parameters;
  std::string address;
  std::shared_ptr<Type> return_type;
  bool same_signature(const Function&);

};

#endif //CPSL_FUNCTION_HPP
