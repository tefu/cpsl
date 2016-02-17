#include "SymbolTable.hpp"

namespace
{
  std::shared_ptr<std::map<std::string, Variable>> SymbolTable;
  std::map<std::string, Expression::Type> types = {
          {"integer", Expression::INTEGER},
          {"char", Expression::CHAR},
          {"boolean", Expression::BOOL},
          {"string", Expression::STRING}
  };
}


std::shared_ptr<std::map<std::string, Variable>> Symbol::get_table()
{
  if (SymbolTable == nullptr)
  {
    SymbolTable = std::make_shared<std::map<std::string, Variable>>();
  }
  return SymbolTable;
}

int Symbol::available_address_offset()
{
  auto winning_address = starting_address;
  bool unique_found = false;
  while(!unique_found)
  {
    unique_found = true;
    for(auto &ident_var_pair: *get_table())
    {
      auto var = ident_var_pair.second;
      if (var.address_offset == winning_address)
      {
        winning_address += 4;
        unique_found = false;
      }
    }

  }

  return winning_address;
}


Expression::Type Symbol::parse_type(std::string raw_type)
{
  if(types.find(raw_type) != types.end())
  {
    return types[raw_type];
  }
  else
  {
    return Expression::INTEGER;
  }
}
