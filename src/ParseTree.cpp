#include "ParseTree.hpp"
#include "SymbolTable.hpp"
#include <stdexcept>
#include <sstream>

extern void yyerror(const char* message);
extern std::stringstream sout;

namespace
{
  Type* find_type(std::string supposed_type)
  {
    auto type = Symbol::lookup_type(supposed_type);
    if (type == nullptr)
    {
      throw std::runtime_error(supposed_type + " is not a type.");
    }
    return type;
  }

  std::string confirm_not_defined(std::string ident)
  {
    if (Symbol::already_defined(ident))
    {
      throw std::runtime_error(ident + " is already defined.");
    }
    return ident;
  }


  void AddVariable(std::string ident, Type* type)
  {
    Symbol::add_variable(confirm_not_defined(ident), type);
  }

  void require_both_as(Expression* left, Expression* right, std::string type_name, std::string operation)
  {
    if (left->data_type()->type() != type_name || right->data_type()->type() != type_name)
      throw std::runtime_error(std::string("Performing ") + operation + " requires both types be " + type_name);
  }

  void require_both_same(Expression* left, Expression* right, std::string operation)
  {
    if(left->data_type()->type() != right->data_type()->type())
      throw std::runtime_error(std::string("Performing ") + operation + " requires both types be the same.");
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

void ParseTree::VarDecl(std::vector<std::string>* identList, Type* type)
{
  for(auto &ident: *identList)
  {
    AddVariable(ident,type);
  }
}

void ParseTree::TypeDecl(std::string* type_name, Type* type)
{
  Symbol::add_type(*type_name, type);
}

void ParseTree::ConstDecl(std::string* ident, Expression* expr)
{
  if (expr->is_constant())
  {
    Symbol::add_constant(*ident, expr);
  }
  else
  {
    throw std::runtime_error(std::string("Defining constant ") +
                             *ident +
                             " to be a non-constant expression.");
  }
}

std::vector<FormalParameter*>* ParseTree::formal_parameter(bool is_var, std::vector<std::string>* argument_list, Type* type)
{
  auto arguments = new std::vector<FormalParameter*>();

  for(auto &arg: *argument_list)
  {
    arguments->push_back(new FormalParameter(is_var, arg, type));
  }
  return arguments;
}

FunctionBlock* ParseTree::procedure_body(std::string* procedure_name, ProgramNode* body)
{
  Symbol::pop_table();
  auto function = Symbol::lookup_function(*procedure_name);
  return new FunctionBlock(function->address, body);
}

std::string* ParseTree::function_decl(std::string* function_name, std::vector<FormalParameter*>* parameters, Type* type)
{
  auto new_function = std::make_shared<Function>(*parameters, type);
  auto duplicate_function = Symbol::lookup_function(*function_name);
  if (duplicate_function != nullptr && !(new_function->same_signature(*duplicate_function)))
  {
    throw std::runtime_error(*function_name + " is already a function with a different signature.");
  }
  else
  {
    Symbol::add_function(*function_name, new_function);
  }

  Symbol::push_table();

  for(auto &param: new_function->parameters)
  {
    if (param->is_variable)
    {
      Symbol::add_argument(param->argument, param->type);
    }
    else
    {
      Symbol::add_reference(param->argument, param->type);
    }
  }

  return function_name;
}

std::string* ParseTree::function_decl(std::string* function_name,std::vector<FormalParameter*>* parameters, std::string* type)
{
  return function_decl(function_name, parameters, find_type(*type));
}

Type* ParseTree::simple_type(std::string* type_name)
{
  return find_type(*type_name);
}

Type* ParseTree::array_type(Expression* lower_bound, Expression* upper_bound, Type* type)
{
  auto lower = lower_bound->flatten_int();
  auto upper = upper_bound->flatten_int();

  if (upper < lower)
  {
    throw std::runtime_error("An array can't have an upper bound less than its lower bound.");
  }

  return new Array(lower, upper - lower + 1, type);
}

Type* ParseTree::record_type(std::vector<RecordMember>* members)
{
  return new Record{members};
}

std::vector<RecordMember>* ParseTree::record_members(std::vector<std::string>* names, Type* type)
{
  auto members = new std::vector<RecordMember>();
  for(auto &&name: *names)
  {
    members->emplace_back(name,type);
  }
  return members;
}

LogicalOr* ParseTree::logical_or(Expression* left, Expression* right)
{
  require_both_as(left, right, Type::boolean_type(), "logical or");
  return new LogicalOr(left, right);
}

LogicalAnd* ParseTree::logical_and(Expression* left, Expression* right)
{
  require_both_as(left, right, Type::boolean_type(), "logical and");
  return new LogicalAnd(left, right);
}

Equality* ParseTree::equality(Expression* left, Expression* right)
{
  require_both_same(left,right,"equality");
  return new Equality(left, right);
}

Inequality* ParseTree::inequality(Expression* left, Expression* right)
{
  require_both_same(left,right,"inequality");
  return new Inequality(left, right);
}

LessThanOrEqual* ParseTree::less_than_or_equal(Expression* left, Expression* right)
{
  require_both_as(left, right, Type::integer_type(), "less than or equal: <=");
  return new LessThanOrEqual(left, right);
}

GreaterThanOrEqual* ParseTree::greater_than_or_equal(Expression* left, Expression* right)
{
  require_both_as(left, right, Type::integer_type(), "greater than or equal: >=");
  return new GreaterThanOrEqual(left, right);
}

LessThan* ParseTree::less_than(Expression* left, Expression* right)
{
  require_both_as(left, right, Type::integer_type(), "less than: <");
  return new LessThan(left, right);
}

GreaterThan* ParseTree::greater_than(Expression* left, Expression* right)
{
  require_both_as(left, right, Type::integer_type(), "greater than: >");
  return new GreaterThan(left, right);
}

OperatorPlus* ParseTree::plus(Expression* left, Expression* right)
{
  require_both_as(left, right, Type::integer_type(), "addition: +");
  return new OperatorPlus(left, right);
}

OperatorMinus* ParseTree::minus(Expression* left, Expression* right)
{
  require_both_as(left, right, Type::integer_type(), "subtraction: -");
  return new OperatorMinus(left, right);
}

OperatorMult* ParseTree::mult(Expression* left, Expression* right)
{
  require_both_as(left, right, Type::integer_type(), "multiplication: *");
  return new OperatorMult(left, right);
}

OperatorDivide* ParseTree::divide(Expression* left, Expression* right)
{
  require_both_as(left, right, Type::integer_type(), "division: /");
  return new OperatorDivide(left, right);
}

OperatorModulus* ParseTree::modulus(Expression* left, Expression* right)
{
  require_both_as(left, right, Type::integer_type(), "modulus: %");
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
    throw std::runtime_error(std::string("I don't know what the function ") + *ident + " is.");
  }

  if(exprList->size() != function->parameters.size())
  {
    throw std::runtime_error(std::string("Incorrect number of arguments to function " + *ident));
  }

  if (!(function->correct_types(*exprList)))
  {
    throw std::runtime_error(std::string("Incorrect type in value of function call: ") + *ident);
  }

  if (!function->correct_references(*exprList))
  {
    throw std::runtime_error(std::string("Cannot send value as a reference in function call: ") + *ident);
  }

  return new FunctionCall(function->parameters, *exprList, function->return_type, function->address, Symbol::size_of_stack());
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
  if (lval == nullptr)
    throw std::runtime_error(std::string("Unknown identifier: ") + *ident);

  return lval;
}

LValue* ParseTree::array_access(LValue* array, Expression* index)
{
  auto subtype = array->get_subtype();
  if (subtype == nullptr)
    throw std::runtime_error("Cannot access LValue like an array.");

  return new ArrayAccess{array, index};
}

LValue* ParseTree::record_field(LValue* record, std::string* field)
{
  auto record_type = record->get_record();
  if (record_type == nullptr)
    throw std::runtime_error("Cannot access the field of a non-record.");

  if (!(record_type->is_field(*field)))
    throw std::runtime_error("Field does not exist in record.");

  return new RecordField{record, record_type, *field};
}


Assignment* ParseTree::assign(LValue* l_val, Expression* expr)
{
  if (l_val->is_constant())
  {
    throw std::runtime_error("Assigning to a constant.");
  }

  return new Assignment(l_val, expr);
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
  AddVariable(*ident, new Integer());
  return l_value(ident);
}

ReturnStatement* ParseTree::return_statement(Expression* expr)
{
  return new ReturnStatement(expr);
}
