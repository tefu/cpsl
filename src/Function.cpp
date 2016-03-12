#include "Function.hpp"

bool Function::same_signature(const Function& other_func)
{
  if (parameters.size() != other_func.parameters.size())
    return false;

  for(size_t i = 0; i < parameters.size() && i < other_func.parameters.size(); i++)
  {
    if (!(*(parameters[i]) == *(other_func. parameters[i])))
      return false;
  }

  return true;
}


bool Function::correct_types(std::vector<Expression*> exprList)
{
  for(auto i = 0; i < parameters.size() && i < exprList.size(); i++)
  {
    auto param = parameters[i];
    auto expr = exprList[i];
    if(!(*(param->type) == *(expr->data_type())))
    {
      return false;
    }
  }
  return true;
}


bool FormalParameter::operator==(const FormalParameter& other_param)
{
  bool same_var = is_variable == other_param.is_variable;
  bool same_type = *type == *other_param.type;
  bool same_arg = argument == other_param.argument;

  return same_var && same_type && same_arg;
}
