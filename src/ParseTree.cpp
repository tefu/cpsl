#include <iostream>
#include "ParseTree.hpp"
#include "SymbolTable.hpp"
#include <sstream>

extern void yyerror(const char* message);
extern std::stringstream sout;

ProgramNode* ParseTree::program(ProgramNode* b)
{
  return b;
}

Block* ParseTree::block(std::vector<ProgramNode*>* statements)
{
  return new Block(statements);
}

void ParseTree::VarDecl(std::vector<std::string>* identList, std::string* type)
{
  for(auto &ident: *identList)
  {
    Symbol::add_variable(ident, *type);
  }
}

void ParseTree::ConstDecl(std::string* ident, Expression* expr)
{
  if (expr->is_constant())
  {
    Symbol::add_constant(*ident, expr);
  }
  else
  {
    yyerror((std::string("Error: defining constant '") + *ident + "' to be a non-constant expression").c_str());
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

LValue* ParseTree::l_value(std::string* ident)
{
  auto var = Symbol::lookup_variable(*ident);
  if (var != nullptr)
    return var;

  auto constant = Symbol::lookup_constant(*ident);
  if (constant != nullptr)
    return constant;

  yyerror((std::string("Unknown identifier: '") + *ident + "'").c_str());
  return nullptr;
}

Assignment* ParseTree::assign(LValue* l_val, Expression* expr)
{
  if (l_val->is_constant())
  {
    yyerror("Assigning to a constant");
  }
  else
  {
    return new Assignment(l_val, expr);
  }
}

ReadStatement* ParseTree::read_statement(std::vector<LValue*>* l_values)
{
  return new ReadStatement(l_values);
}

WriteStatement* ParseTree::write_statement(std::vector<Expression*>* exprs)
{
  return new WriteStatement(exprs);
}

IfStatement* ParseTree::if_statement(Expression* expr,
                                     std::vector<ProgramNode*>* main_statements,
                                     std::vector<ElseIf*>* optional_else_ifs,
                                     std::vector<ProgramNode*>* optional_else)
{
  return new IfStatement{expr, main_statements, optional_else_ifs, optional_else};
}


ElseIf* ParseTree::else_if(Expression* expr, std::vector<ProgramNode*>* statements)
{
  return new ElseIf{expr, statements};
}

WhileStatement* ParseTree::while_statement(Expression* expr,std::vector<ProgramNode*>* statements)
{
  return new WhileStatement(expr, statements);
}

RepeatStatement* ParseTree::repeat_statement(Expression* expr,std::vector<ProgramNode*>* statements)
{
  return new RepeatStatement(expr, statements);
}

ForStatement* ParseTree::for_statement(std::string* ident,
                                       Expression* start,
                                       bool going_up,
                                       Expression* end,
                                       std::vector<ProgramNode*>* statements)
{
  auto var = l_value(ident);
  auto assignment = assign(var, start);
  Expression* condition;
  ProgramNode* update;
  if (going_up)
  {
    condition = less_than_or_equal(var->read(), end);
    update = assign(var, SUCC(var->read()));
  }
  else
  {
    condition = greater_than_or_equal(var->read(), end);
    update = assign(var, PRED(var->read()));
  }
  return new ForStatement(assignment, condition, statements, update);
}