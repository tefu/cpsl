#include <iostream>
#include "catch.hpp"
#include "Expression.hpp"

TEST_CASE("Expressions")
{
  auto lor = new LogicalOr{new BoolLiteral{true}, new BoolLiteral{false}};
  std::cout << lor->gen_asm();
  lor->release();
  delete lor;
  auto land = new LogicalAnd{new BoolLiteral{true}, new BoolLiteral{false}};
  delete land;
  auto greater = new GreaterThan{new IntLiteral{10}, new IntLiteral{2}};
  delete greater;
  auto less = new LessThan{new IntLiteral{10}, new IntLiteral{2}};
  delete less;
  auto equal = new Equality{new IntLiteral{10}, new IntLiteral{2}};
  delete equal;
  auto inequal = new Inequality{new IntLiteral{10}, new IntLiteral{2}};
  delete inequal;


  SECTION("Registers are allocated incrementally from 8.")
  {
    auto literal = new std::string("hello!");
    auto a = new StringLiteral(literal);
    auto b = new IntLiteral(999);
    auto c = new IntLiteral(-20);

    a->allocate();
    b->allocate();
    c->allocate();
    REQUIRE(a->result() == 8);
    REQUIRE(b->result() == 9);
    REQUIRE(c->result() == 10);

    a->release();

    REQUIRE(a->result() == -1);
    REQUIRE(b->result() == 9);
    REQUIRE(c->result() == 10);

    b->release();

    REQUIRE(a->result() == -1);
    REQUIRE(b->result() == -1);
    REQUIRE(c->result() == 10);

    b->allocate();
    a->allocate();

    REQUIRE(a->result() == 9);
    REQUIRE(b->result() == 8);
    REQUIRE(c->result() == 10);

  }

}