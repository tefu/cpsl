#include <iostream>
#include "ParseTree.hpp"
#include "SymbolTable.hpp"
#include <sstream>

extern void yyerror(const char* message);
extern std::stringstream sout;

namespace
{
  std::shared_ptr<Type> find_type(std::string supposed_type)
  {
    auto type = Symbol::lookup_type(supposed_type);
    if (type == nullptr)
    {
      std::stringstream s;
      s << "Error: " << supposed_type << " is not a type.";
      yyerror(s.str().c_str());
    }
    return type;
  }
}

ProgramNode* ParseTree::program(std::vector<ProgramNode*>* bodies, ProgramNode* main)
{
  return new Program(*bodies, main);
}

Block* ParseTree::block(std::vector<ProgramNode*>* statements)
{
  return new Block(statements);
}

void ParseTree::VarDecl(std::vector<std::string>* identList, std::string* type)
{
  for(auto &ident: *identList)
  {
    Symbol::add_variable(ident, find_type(*type));
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

FormalParameter* ParseTree::formal_parameter(bool is_var, std::vector<std::string>* argument_list, std::string* supposed_type)
{
  std::vector<std::shared_ptr<Type>> argument_types;
  auto type = find_type(*supposed_type);
  return new FormalParameter(is_var, *argument_list, type);
}

FunctionBlock* ParseTree::procedure_body(std::string* procedure_name, ProgramNode* body)
{
  Symbol::pop_table();
  auto function = Symbol::lookup_function(*procedure_name);
  return new FunctionBlock(function->address, body);
}

std::string* ParseTree::function_decl(std::string* function_name, std::vector<FormalParameter*>* parameters, std::shared_ptr<Type> type)
{
  auto new_function = std::make_shared<Function>(*parameters, type);
  auto duplicate_function = Symbol::lookup_function(*function_name);
  if (duplicate_function != nullptr && !(new_function->same_signature(*duplicate_function)))
  {
    std::stringstream s;
    s << "Error: " << *function_name << " is already a function with a different signature.";
    yyerror(s.str().c_str());
  }
  else
  {
    Symbol::add_function(*function_name, new_function);
  }

  Symbol::push_table();

  for(auto &param: *parameters)
  {
    if (param->is_variable)
    {
      for (auto &arg_name: param->arguments)
      {
        Symbol::add_argument(arg_name, param->type);
      }
    }
    else
    {
      // TODO: implement reference variables
    }
  }

  return function_name;
}

std::string* ParseTree::function_decl(std::string* function_name,std::vector<FormalParameter*>* parameters, std::string* type)
{
  return function_decl(function_name, parameters, find_type(*type));
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

FunctionCall* ParseTree::function_call(std::string* ident, std::vector<Expression*>* exprList)
{
  auto function = Symbol::lookup_function(*ident);
  if (function == nullptr)
  {
    std::stringstream s;
    s << "I don't know what the function " << *ident << " is.";
    yyerror(s.str().c_str());
  }

  auto total_parameters_expected = 0;
  for(auto &args: function->parameters)
  {
    total_parameters_expected += args->arguments.size();
  }

  if(exprList->size() != total_parameters_expected)
  {
    std::stringstream s;
    s << "Incorrect number of arguments to function " << *ident;
    yyerror(s.str().c_str());
  }
  for(auto i = 0; i < function->parameters.size() && i < exprList->size(); i++)
  {
    auto param = function->parameters[i];
    auto expr = (*exprList)[i];
    if(param->type->type() != expr->data_type()->type())
    {
      std::stringstream s;
      s << "Incorrect type in function call " << *ident;
      yyerror(s.str().c_str());
    }
  }
  return new FunctionCall(*exprList, function->return_type, function->address, Symbol::size_of_stack());
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
  auto lval = Symbol::lookup(*ident);
  if (lval != nullptr)
    return lval;

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

ForStatement* ParseTree::for_statement(LValue* var,
                                       Expression* start,
                                       bool going_up,
                                       Expression* end,
                                       std::vector<ProgramNode*>* statements)
{
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

LValue* ParseTree::for_head(std::string* ident)
{
  Symbol::add_variable(*ident, std::make_shared<Integer>());
  return l_value(ident);
}

ReturnStatement* ParseTree::return_statement(Expression* expr)
{
  return new ReturnStatement(expr);
}
