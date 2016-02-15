#include "Expression.hpp"

namespace
{
  bool is_binary_operation_constant(const Expression* right, const Expression* left)
  {
    return left->is_constant() && right->is_constant();
  }
}

std::string LogicalOr::gen_asm() const
{
  return "";
}
bool LogicalOr::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type LogicalOr::data_type() const
{
  return Expression::BOOL;
}




std::string LogicalAnd::gen_asm() const
{
  return "";
}
bool LogicalAnd::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type LogicalAnd::data_type() const
{
  return Expression::BOOL;
}


std::string Equality::gen_asm() const
{
  return "";
}
bool Equality::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type Equality::data_type() const
{
  return Expression::BOOL;
}


std::string Inequality::gen_asm() const
{
  return "";
}
bool Inequality::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type Inequality::data_type() const
{
  return Expression::BOOL;
}


std::string LessThanOrEqual::gen_asm() const
{
  return "";
}
bool LessThanOrEqual::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type LessThanOrEqual::data_type() const
{
  return Expression::BOOL;
}


std::string LessThan::gen_asm() const
{
  return "";
}
bool LessThan::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type LessThan::data_type() const
{
  return Expression::BOOL;
}


std::string GreaterThanOrEqual::gen_asm() const
{
  return "";
}
bool GreaterThanOrEqual::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type GreaterThanOrEqual::data_type() const
{
  return Expression::BOOL;
}


std::string GreaterThan::gen_asm() const
{
  return "";
}
bool GreaterThan::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type GreaterThan::data_type() const
{
  return Expression::BOOL;
}


std::string OperatorPlus::gen_asm() const
{
  return "";
}
bool OperatorPlus::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type OperatorPlus::data_type() const
{
  return Expression::INTEGER;
}


std::string OperatorMinus::gen_asm() const
{
  return "";
}
bool OperatorMinus::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type OperatorMinus::data_type() const
{
  return Expression::INTEGER;
}


std::string OperatorMult::gen_asm() const
{
  return "";
}
bool OperatorMult::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type OperatorMult::data_type() const
{
  return Expression::INTEGER;
}


std::string OperatorDivide::gen_asm() const
{
  return "";
}
bool OperatorDivide::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type OperatorDivide::data_type() const
{
  return Expression::INTEGER;
}

std::string OperatorModulus::gen_asm() const
{
  return "";
}
bool OperatorModulus::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type OperatorModulus::data_type() const
{
  return Expression::INTEGER;
}

std::string Negation::gen_asm() const
{
  return "";
}
bool Negation::is_constant() const
{
  return expr->is_constant();
}
Expression::Type Negation::data_type() const
{
  return Expression::BOOL;
}

std::string UnaryMinus::gen_asm() const
{
  return "";
}
bool UnaryMinus::is_constant() const
{
  return expr->is_constant();
}
Expression::Type UnaryMinus::data_type() const
{
  return Expression::INTEGER;
}


std::string FunctionCall::gen_asm() const
{
  return "";
}
bool FunctionCall::is_constant() const
{
  for(auto &expr: *exprList)
  {
    if (!expr->is_constant())
      return false;
  }
  return true;
}
Expression::Type FunctionCall::data_type() const
{
  // TODO: look up type declaration.
  return Expression::INTEGER;

}


std::string ToChar::gen_asm() const
{
  return "";
}
bool ToChar::is_constant() const
{
  return expr->is_constant();
}
Expression::Type ToChar::data_type() const
{
  return Expression::CHAR;
}


std::string ToInt::gen_asm() const
{
  return "";
}
bool ToInt::is_constant() const
{
  return expr->is_constant();
}
Expression::Type ToInt::data_type() const
{
  return Expression::INTEGER;
}


std::string Predecessor::gen_asm() const
{
  return "";
}
bool Predecessor::is_constant() const
{
  return expr->is_constant();
}
Expression::Type Predecessor::data_type() const
{
  return expr->data_type();
}


std::string Successor::gen_asm() const
{
  return "";
}
bool Successor::is_constant() const
{
  return expr->is_constant();
}
Expression::Type Successor ::data_type() const
{
  return expr->data_type();
}


std::string StringLiteral::gen_asm() const
{
  
}

bool StringLiteral::is_constant() const
{
  
}
Expression::Type StringLiteral::data_type() const
{
  
}

std::string IntLiteral::gen_asm() const
{
  
}
bool IntLiteral::is_constant() const
{
  
}
Expression::Type IntLiteral::data_type() const
{
  
}

std::string BoolLiteral::gen_asm() const
{
  
}
bool BoolLiteral::is_constant() const
{
  
}
Expression::Type BoolLiteral::data_type() const
{
  
}


std::string LValue::gen_asm() const
{
  return "";
}
bool LValue::is_constant() const
{
  return false;
}

Expression::Type LValue::data_type() const
{
  return Expression::INTEGER;
}
