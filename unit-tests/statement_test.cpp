#include <iostream>
#include "Expression.hpp"
#include "Statement.hpp"
#include "catch.hpp"

TEST_CASE("If statements make sense")
{
  auto should_be_true = new BoolLiteral(true);
  auto exprs = new std::vector<Expression*>;
  exprs->push_back(should_be_true);
  auto write_it_out = new WriteStatement(exprs);
  auto statements = new std::vector<ProgramNode*>;
  statements->push_back(write_it_out);
  auto basic_if = new IfStatement(should_be_true, statements, nullptr, nullptr);

  std::cout << basic_if->gen_asm() << std::endl;
}