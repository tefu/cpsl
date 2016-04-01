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

bool Function::correct_types(std::vector<Type*> types)
{
  if(parameters.size() != types.size())
  {
    return false;
  }

  for(auto i = 0; i < parameters.size() && i < types.size(); i++)
  {
    auto param = parameters[i];
    auto type = types[i];
    if(!(*(param->type) == *type))
    {
      return false;
    }
  }

  return true;
}

bool Function::correct_references(std::vector<Expression*> exprList)
{
  if(parameters.size() != exprList.size())
  {
    return false;
  }

  for(auto i = 0; i < parameters.size() && i < exprList.size(); i++)
  {
    auto param = parameters[i];
    auto expr = exprList[i];
    if(!(param->is_variable || expr->can_be_referenced()))
    {
      return false;
    }
  }

  return true;
}
