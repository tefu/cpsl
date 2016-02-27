#include "SymbolTable.hpp"

namespace
{
  auto global_offset = 0;
  auto variables = std::make_shared<std::map<std::string, std::shared_ptr<Variable>>>();
  auto constants = std::make_shared<std::map<std::string, std::shared_ptr<Constant>>>();
  std::map<std::string, Type> types = {
          {"integer", Integer{}},
          {"char", Character{}},
          {"boolean", Boolean{}},
          {"string", StringConstant{}}
  };

  Type parse_type(std::string raw_type)
  {
    if(types.find(raw_type) != types.end())
    {
      return types[raw_type];
    }
    else
    {
      return Integer{};
    }
  }

  void init_check()
  {
    if (constants->empty())
    {
      constants->emplace(std::string("true"), std::make_shared<Constant>(new BoolLiteral(true)));
      constants->emplace(std::string("True"), std::make_shared<Constant>(new BoolLiteral(true)));
      constants->emplace(std::string("false"), std::make_shared<Constant>(new BoolLiteral(false)));
      constants->emplace(std::string("False"), std::make_shared<Constant>(new BoolLiteral(false)));
    }
  }

}


void Symbol::add_variable(std::string ident, std::string supposed_type) {
  auto type = types[supposed_type];
  auto var = std::shared_ptr{new Variable{type, global_offset}};
  variables->emplace(std::string(ident), var);
  global_offset += type.word_size();
}

void Symbol::add_constant(std::string ident, Expression* expr)
{
  constants->emplace(std::string(ident), expr);
}

std::shared_ptr<Variable> lookup_variable(std::string ident)
{
  if (variables->find(ident) != variables->end())
  {
    return (*variables)[ident];
  }
  else
  {
    return nullptr;
  }
}

std::shared_ptr<Constant> lookup_constant(std::string ident)
{
  if (constants->find(ident) != constants->end())
  {
    return (*constants)[ident];
  }
  else
  {
    return nullptr;
  }
}