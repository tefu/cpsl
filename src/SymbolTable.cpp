#include "SymbolTable.hpp"

namespace
{
  auto global_offset = 0;
  auto variables = std::make_shared<std::map<std::string, Variable*>>();
  auto constants = std::make_shared<std::map<std::string, Constant*>>();
  auto types = std::make_shared<std::map<std::string, std::shared_ptr<Type>>>();

  std::shared_ptr<Type> parse_type(std::string raw_type)
  {
    if(types->find(raw_type) != types->end())
    {
      return (*types)[raw_type];
    }
    else
    {
      return nullptr;
    }
  }

  void init_check()
  {
    if (constants->empty())
    {
      constants->emplace(std::string("true"), new Constant(new BoolLiteral(true)));
      constants->emplace(std::string("True"), new Constant(new BoolLiteral(true)));
      constants->emplace(std::string("false"), new Constant(new BoolLiteral(false)));
      constants->emplace(std::string("False"), new Constant(new BoolLiteral(false)));
    }

    if (types->empty())
    {
      types->emplace(std::string("integer"), std::make_shared<Integer>());
      types->emplace(std::string("char"), std::make_shared<Character>());
      types->emplace(std::string("boolean"), std::make_shared<Boolean>());
      types->emplace(std::string("string"), std::make_shared<StringConstant>());
    }
  }

}

void Symbol::add_variable(std::string ident, std::string supposed_type) {
  init_check();
  auto type = parse_type(supposed_type);
  auto var = new Variable{type, global_offset};
  variables->emplace(std::string(ident), var);
  global_offset += type->word_size();
}

void Symbol::add_constant(std::string ident, Expression* expr)
{
  init_check();
  constants->emplace(std::string(ident), new Constant(expr));
}

LValue* Symbol::lookup(std::string ident)
{
  init_check();
  if (variables->find(ident) != variables->end())
    return (*variables)[ident];

  if (constants->find(ident) != constants->end())
    return (*constants)[ident];

  return nullptr;
}