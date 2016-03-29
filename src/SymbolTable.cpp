#include <assert.h>
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

  auto global_offset = 0;

  struct SymbolTable
  {
    SymbolTable(int s_offset, int f_offset)
            : lvalues(std::make_shared<std::map<std::string, LValue*>>()),
              stack_offset(s_offset),
              frame_offset(f_offset),
              types(std::make_shared<std::map<std::string, Type*>>()),
              functions(std::make_shared<std::map<std::string, std::shared_ptr<Function>>>()){}
    int stack_offset;
    int frame_offset;
    std::shared_ptr<std::map<std::string, Type*>> types;
    std::shared_ptr<std::map<std::string, std::shared_ptr<Function>>> functions;
    std::shared_ptr<std::map<std::string, LValue*>> lvalues;

    Type* parse_type(std::string raw_type)
    {
      return find_in_map(*types, raw_type);
    }

    std::shared_ptr<Function> find_function(std::string name)
    {
      return find_in_map(*functions, name);
    }

    LValue* find_lvalue(std::string ident)
    {
      return find_in_map(*lvalues, ident);
    }
  };

  auto tables = std::vector<SymbolTable>();

  bool next_variable_on_stack()
  {
    return tables.size() > 1;
  }
}

void Symbol::init()
{
  if(tables.empty())
  {
    SymbolTable first_table(0,0);
    first_table.lvalues->emplace(std::string("true"), new Constant(new BoolLiteral(true)));
    first_table.lvalues->emplace(std::string("TRUE"), new Constant(new BoolLiteral(true)));
    first_table.lvalues->emplace(std::string("false"), new Constant(new BoolLiteral(false)));
    first_table.lvalues->emplace(std::string("FALSE"), new Constant(new BoolLiteral(false)));
    first_table.types->emplace(std::string("integer"), new Integer());
    first_table.types->emplace(std::string("char"), new Character());
    first_table.types->emplace(std::string("boolean"), new Boolean());
    tables.push_back(first_table);
  }
}

void Symbol::add_variable(std::string ident, Type* type) {
  assert (type != nullptr);
  SymbolTable& last_table = tables.back();
  if (next_variable_on_stack())
  {
    last_table.stack_offset -= type->word_size();
    auto var = new StackVariable{type, last_table.stack_offset};
    last_table.lvalues->emplace(std::string(ident), var);
  }
  else
  {
    auto var = new GlobalVariable{type, global_offset};
    last_table.lvalues->emplace(std::string(ident), var);
    global_offset += type->word_size();
  }
}

void Symbol::add_argument(std::string ident, Type* type)
{
  assert (type != nullptr);
  SymbolTable& last_table = tables.back();
  last_table.frame_offset -= type->word_size();
  auto arg = new VarArgument{type, last_table.frame_offset};
  last_table.lvalues->emplace(std::string(ident), arg);
}

void Symbol::add_reference(std::string ident, Type* type)
{
  assert (type != nullptr);
  SymbolTable& last_table = tables.back();
  last_table.frame_offset -= Type::ADDRESS_SIZE;
  auto arg = new RefArgument{type, last_table.frame_offset};
  last_table.lvalues->emplace(std::string(ident), arg);
}

void Symbol::add_constant(std::string ident, Expression* expr)
{
  auto last_table = tables.back();
  last_table.lvalues->emplace(std::string(ident), new Constant(expr));
}

void Symbol::add_function(std::string name, std::shared_ptr<Function> func)
{
  auto last_table = tables.back();
  last_table.functions->emplace(name, func);
}

void Symbol::add_type(std::string name, Type* type)
{
  auto last_table = tables.back();
  last_table.types->emplace(name, type);
}


LValue* Symbol::lookup(std::string ident)
{
  for (size_t i = tables.size(); i-- > 0;)
  {
    auto table = tables[i];
    auto lvalue = table.find_lvalue(ident);
    if (lvalue != nullptr)
      return lvalue;
  }

  return nullptr;
}

Type* Symbol::lookup_type(std::string supposed_type)
{
  for (size_t i = tables.size(); i-- > 0;)
  {
    auto table = tables[i];
    auto type = table.parse_type(supposed_type);
    if (type != nullptr)
      return type;
  }
  return nullptr;
}

std::shared_ptr<Function> Symbol::lookup_function(std::string function_name)
{
  for (size_t i = tables.size(); i-- > 0;)
  {
    auto table = tables[i];
    auto function = table.find_function(function_name);
    if (function != nullptr)
      return function;
  }
  return nullptr;
}

void Symbol::push_table()
{
  auto last_table = tables.back();
  SymbolTable new_table(0,0);
  tables.push_back(new_table);
}

void Symbol::pop_table()
{
  tables.pop_back();
}

int Symbol::size_of_stack()
{
  auto total_size = 0;
  auto last_table = tables.back();
  for (auto &pair: *last_table.lvalues)
  {
    total_size += pair.second->size_on_stack();
  }
  return total_size;
}

bool Symbol::already_defined(std::string ident)
{
  auto table = tables.back();
  auto function = table.find_function(ident);
  auto type = table.parse_type(ident);
  auto l_value = table.find_lvalue(ident);
  return (function != nullptr || type != nullptr || l_value != nullptr);
}
