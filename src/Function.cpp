#include "Function.hpp"

namespace
{
  template<typename F>
  bool all_correct(F correct, Function func, std::vector<Expression*> exprList)
  {
    for(auto i = 0; i < func.parameters.size() && i < exprList.size(); i++)
      {
        auto param = func.parameters[i];
        auto expr = exprList[i];
        if(!correct(param,expr))
        {
          return false;
        }
      }
    return true;
  }
}

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
  return all_correct([](FormalParameter* param, Expression* expr){
      return param->type->type() == expr->data_type()->type();
    }, *this, exprList);
}

bool Function::correct_references(std::vector<Expression*> exprList)
{
  return all_correct([](FormalParameter* param, Expression* expr){
      return (param->is_variable || expr->can_be_referenced());
    }, *this, exprList);
}