#include <iostream>
#include "catch.hpp"
#include "instructions.hpp"

TEST_CASE("Starting register is 8.")
{
  auto literal = new std::string("hello!");
  auto expr = new StringLiteral(literal);
  REQUIRE(expr->result() == -1);
  expr->allocate();
  REQUIRE(expr->result() == 8);
  expr->release();
  REQUIRE(expr->result() == -1);
}

TEST_CASE("Registers are allocated incrementally.")
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