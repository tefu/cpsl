#include "Function.hpp"

bool Function::same_signature(const Function& other_func)
{
  if (parameters.size() != other_func.parameters.size())
    return false;

  for(size_t i = 0; i < parameters.size() && i < other_func.parameters.size(); i++)
  {
    if (!(parameters[i] == other_func.parameters[i]))
      return false;
  }

  return true;
}

bool FormalParameter::operator==(const FormalParameter& other_param)
{
  bool same_var = is_variable == other_param.is_variable;
  bool same_type = type->type() == other_param.type->type();

  bool same_arguments = true;
  if (arguments.size() != other_param.arguments.size())
    same_arguments = false;

  for(size_t i = 0; i < arguments.size() && i < other_param.arguments.size(); i++)
  {
    if (arguments[i].compare(other_param.arguments[i]) != 0)
      same_arguments = false;
  }


  return same_var && same_type && same_arguments;

}