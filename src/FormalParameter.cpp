#include "FormalParameter.hpp"

bool FormalParameter::operator==(const FormalParameter& other_param)
{
  bool same_var = is_variable == other_param.is_variable;
  bool same_type = *type == *other_param.type;
  bool same_arg = argument == other_param.argument;

  return same_var && same_type && same_arg;
}
