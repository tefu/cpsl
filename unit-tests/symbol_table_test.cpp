#include <iostream>
#include "Type.hpp"
#include "SymbolTable.hpp"
#include "catch.hpp"

TEST_CASE("Symbol table works")
{
  Integer my_int{};
  REQUIRE(my_int.type() == Type::INTEGER);
  Symbol::add_variable(std::string("x"), std::string("integer"));
  Symbol::add_variable(std::string("y"), std::string("boolean"));
  Symbol::add_variable(std::string("z"), std::string("string"));

  auto x_var = Symbol::lookup_variable("x");
  REQUIRE(x_var != nullptr);
  REQUIRE(x_var->address_offset == 0);
  REQUIRE(x_var->type.type() == Type::INTEGER);
  REQUIRE(x_var->type.word_size() == 4);

  auto y_var = Symbol::lookup_variable("y");
  REQUIRE(y_var != nullptr);
  REQUIRE(y_var->address_offset == 4);
  REQUIRE(y_var->type.type() == Type::BOOL);
  REQUIRE(y_var->type.word_size() == 4);

  auto z_var =  Symbol::lookup_variable("z");
  REQUIRE(z_var != nullptr);
  REQUIRE(z_var->address_offset == 8);
  REQUIRE(z_var->type.type() == Type::STRING);
  REQUIRE(z_var->type.word_size() == 4);
}