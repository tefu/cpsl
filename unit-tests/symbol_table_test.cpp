#include <iostream>
#include "Type.hpp"
#include "SymbolTable.hpp"
#include "catch.hpp"

TEST_CASE("Symbol table works")
{
  Integer my_int{};
  REQUIRE(my_int.type() == Type::INTEGER);
  Symbol::add_variable(std::string("x"), std::make_shared<Integer>());


  auto x_var = Symbol::lookup("x");
  REQUIRE(x_var != nullptr);
  REQUIRE(x_var->is_constant() == false);
  REQUIRE(x_var->get_type()->type() == Type::INTEGER);

  Symbol::push_table();
  Symbol::add_variable(std::string("y"), std::make_shared<Boolean>());

  auto y_var = Symbol::lookup("y");
  REQUIRE(y_var != nullptr);
  REQUIRE(y_var->is_constant() == false);
  REQUIRE(y_var->get_type()->type() == Type::BOOL);

  Symbol::pop_table();
  auto non_existant_y = Symbol::lookup("y");
  REQUIRE(non_existant_y == nullptr);

  Symbol::add_constant(std::string("z"), new StringLiteral(new std::string("string")));
  auto z_const = Symbol::lookup("z");
  REQUIRE(z_const != nullptr);
  REQUIRE(z_const->is_constant());
  REQUIRE(z_const->get_type()->type() == Type::STRING);
}
