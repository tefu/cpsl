#include "SymbolTable.hpp"

namespace
{
  template<typename T>
  T find_in_map(std::map<std::string, T> dict, std::string key)
  {
    if(dict.find(key) != dict.end())
    {
      return dict[key];
    }
    else
    {
      return nullptr;
    }
  }

  struct SymbolTable
  {
    SymbolTable(int g_offset) : variables(std::make_shared<std::map<std::string, Variable*>>()),
                    constants(std::make_shared<std::map<std::string, Constant*>>()),
                    global_offset(g_offset),
                    types(std::make_shared<std::map<std::string, std::shared_ptr<Type>>>()){}
    int global_offset;
    std::shared_ptr<std::map<std::string, std::shared_ptr<Type>>> types;
    std::shared_ptr<std::map<std::string, Variable*>> variables;
    std::shared_ptr<std::map<std::string, Constant*>> constants;

    std::shared_ptr<Type> parse_type(std::string raw_type)
    {
      return find_in_map(*types, raw_type);
    }

    Variable* find_variable(std::string ident)
    {
      return find_in_map(*variables, ident);
    }

    Constant* find_constant(std::string ident)
    {
      return find_in_map(*constants, ident);
    }
  };

  auto tables = std::vector<SymbolTable>();

  void init_check()
  {
    if(tables.empty())
    {
      SymbolTable first_table(0);
      first_table.constants->emplace(std::string("true"), new Constant(new BoolLiteral(true)));
      first_table.constants->emplace(std::string("True"), new Constant(new BoolLiteral(true)));
      first_table.constants->emplace(std::string("false"), new Constant(new BoolLiteral(false)));
      first_table.constants->emplace(std::string("False"), new Constant(new BoolLiteral(false)));
      first_table.types->emplace(std::string("integer"), std::make_shared<Integer>());
      first_table.types->emplace(std::string("char"), std::make_shared<Character>());
      first_table.types->emplace(std::string("boolean"), std::make_shared<Boolean>());
      first_table.types->emplace(std::string("string"), std::make_shared<StringConstant>());
      tables.push_back(first_table);
    }
  }
}

void Symbol::add_variable(std::string ident, std::string supposed_type) {
  init_check();
  for (size_t i = tables.size(); i-- > 0;)
  {
    auto table = tables[i];
    auto type = table.parse_type(supposed_type);
    if (type != nullptr)
    {
      SymbolTable& last_table = tables.back();
      auto var = new Variable{type, last_table.global_offset};
      last_table.variables->emplace(std::string(ident), var);
      last_table.global_offset += type->word_size();
      return;
    }
  }
}

void Symbol::add_constant(std::string ident, Expression* expr)
{
  init_check();
  auto last_table = tables.back();
  last_table.constants->emplace(std::string(ident), new Constant(expr));
}

LValue* Symbol::lookup(std::string ident)
{
  init_check();

  for (size_t i = tables.size(); i-- > 0;)
  {
    auto table = tables[i];
    auto var = table.find_variable(ident);
    if (var != nullptr)
      return var;

    auto constant = table.find_constant(ident);
    if (constant != nullptr)
      return constant;
  }

  return nullptr;
}

void Symbol::push_table()
{
  init_check();

  auto last_table = tables.back();
  SymbolTable new_table(last_table.global_offset);
  tables.push_back(new_table);
}

void Symbol::pop_table()
{
  init_check();
  tables.pop_back();
}
