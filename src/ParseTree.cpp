#include <iostream>
#include "ParseTree.hpp"
#include "SymbolTable.hpp"
#include <sstream>
extern std::stringstream sout;

ProgramNode* ParseTree::program(ProgramNode* b)
{
  for(auto &pair: *Symbol::get_table())
  {
    auto printType = [](Expression::Type t) {
      switch (t)
      {
        case Expression::INTEGER:
          return "Integer";
        case Expression::BOOL:
          return "Bool";
        case Expression::CHAR:
          return "Char";
        case Expression::STRING:
        default:
          return "String";
      }
    };
    std::cout << "Identifier: " << pair.first << std::endl;
    std::cout << "Type: " << printType(pair.second.type) << std::endl;
    std::cout << "Address offset: " << pair.second.address_offset << std::endl;
    std::cout << "Constant: " << (pair.second.is_constant ? "true" : "false") << std::endl;
  }
  return b;
}

Block* ParseTree::block(std::vector<ProgramNode*>* statements)
{
  return new Block(statements);
}

void ParseTree::VarDecl(std::vector<std::string>* identList, std::string* type)
{
  auto eType = Symbol::parse_type(*type);
  for(auto &ident: *identList)
  {
    auto address_offset = Symbol::available_address_offset();
    auto var = Variable{eType, address_offset, false};
    Symbol::get_table()->insert({ident,var});
  }
}


LogicalOr* ParseTree::logical_or(Expression* left, Expression* right)
{
  return new LogicalOr(left, right);
}

LogicalAnd* ParseTree::logical_and(Expression* left, Expression* right)
{
  return new LogicalAnd(left, right);
}

Equality* ParseTree::equality(Expression* left, Expression* right)
{
  return new Equality(left, right);
}

Inequality* ParseTree::inequality(Expression* left, Expression* right)
{
  return new Inequality(left, right);
}

LessThanOrEqual* ParseTree::less_than_or_equal(Expression* left, Expression* right)
{
  return new LessThanOrEqual(left, right);
}

GreaterThanOrEqual* ParseTree::greater_than_or_equal(Expression* left, Expression* right)
{
  return new GreaterThanOrEqual(left, right);
}

LessThan* ParseTree::less_than(Expression* left, Expression* right)
{
  return new LessThan(left, right);
}

GreaterThan* ParseTree::greater_than(Expression* left, Expression* right)
{
  return new GreaterThan(left, right);
}

OperatorPlus* ParseTree::plus(Expression* left, Expression* right)
{
  return new OperatorPlus(left, right);
}

OperatorMinus* ParseTree::minus(Expression* left, Expression* right)
{
  return new OperatorMinus(left, right);
}

OperatorMult* ParseTree::mult(Expression* left, Expression* right)
{
  return new OperatorMult(left, right);
}

OperatorDivide* ParseTree::divide(Expression* left, Expression* right)
{
  return new OperatorDivide(left, right);
}

OperatorModulus* ParseTree::modulus(Expression* left, Expression* right)
{
  return new OperatorModulus(left, right);
}

Negation* ParseTree::negation(Expression* expr)
{
  return new Negation(expr);
}

UnaryMinus* ParseTree::unary_minus(Expression* expr)
{
  return new UnaryMinus(expr);
}

FunctionCall* ParseTree::function_call(std::vector<Expression*>* exprList)
{
  return new FunctionCall(exprList);
}

ToChar* ParseTree::CHR(Expression* expr)
{
  return new ToChar(expr);
}

ToInt* ParseTree::ORD(Expression* expr)
{
  return new ToInt(expr);
}

Predecessor* ParseTree::PRED(Expression* expr)
{
  return new Predecessor(expr);
}

Successor* ParseTree::SUCC(Expression* expr)
{
  return new Successor(expr);
}

CharLiteral* ParseTree::char_literal(std::string* literal)
{
  return new CharLiteral(literal);
}

StringLiteral* ParseTree::string_literal(std::string* literal)
{
  return new StringLiteral(literal);
}

IntLiteral* ParseTree::integer_literal(int literal)
{
  return new IntLiteral(literal);
}

LValue* ParseTree::l_value()
{
  return new LValue();
}
