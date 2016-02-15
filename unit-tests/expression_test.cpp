#include "catch.hpp"
#include "Expression.hpp"

TEST_CASE("Expressions", "")
{
  auto lor = new LogicalOr{new BoolLiteral{true}, new BoolLiteral{false}};
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

}