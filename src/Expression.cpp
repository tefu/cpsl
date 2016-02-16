#include <set>
#include "Expression.hpp"
#include "instructions.hpp"

namespace
{
  bool is_binary_operation_constant(const Expression* right, const Expression* left)
  {
    return left->is_constant() && right->is_constant();
  }

  std::set<int> registers_taken = {};
  const int starting_register=8;

  int allocate_register()
  {
    int winning_register = starting_register;
    while(registers_taken.find(winning_register) != registers_taken.end())
    {
      winning_register++;
    }
    registers_taken.insert(winning_register);

    return winning_register;
  }

  void release_register(int reg)
  {
    registers_taken.erase(reg);
  }

  template <typename F>
  std::string binary_operation(F func, Expression* head, Expression* left, Expression* right, std::string note)
  {
    std::stringstream s;
    s << left->gen_asm();
    s << right->gen_asm();
    head->allocate();
    auto dest = head->result();
    auto src1 = left->result();
    auto src2 = right->result();
    s << func(dest, src1, src2, note);
    left->release();
    right->release();

    return s.str();
  }
}

int Expression::result() const
{
  return result_reg;
}

void Expression::allocate()
{
  if (result_reg == NULL_REGISTER)
    result_reg = allocate_register();
}

void Expression::release()
{
  release_register(result_reg);
  result_reg = NULL_REGISTER;
}



/* Binary Operators
   ------------------------------------------------------------------- */
std::string LogicalOr::gen_asm()
{
  return binary_operation(MIPS::logical_or, this, left, right, "Performing logical OR");
}
bool LogicalOr::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type LogicalOr::data_type() const
{
  return Expression::BOOL;
}


std::string LogicalAnd::gen_asm()
{
  return binary_operation(MIPS::logical_and, this, left, right, "Performing logical AND");
}
bool LogicalAnd::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type LogicalAnd::data_type() const
{
  return Expression::BOOL;
}


std::string Equality::gen_asm()
{
  return binary_operation(MIPS::equality, this, left, right, "Performing equality check");
}
bool Equality::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type Equality::data_type() const
{
  return Expression::BOOL;
}


std::string Inequality::gen_asm()
{
  return binary_operation(MIPS::inequality, this, left, right, "Performing inequality check");
}
bool Inequality::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type Inequality::data_type() const
{
  return Expression::BOOL;
}


std::string LessThanOrEqual::gen_asm()
{
  return binary_operation(MIPS::less_than_or_equal, this, left, right, "Performing <= check");
}
bool LessThanOrEqual::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type LessThanOrEqual::data_type() const
{
  return Expression::BOOL;
}


std::string LessThan::gen_asm()
{
  return binary_operation(MIPS::less_than, this, left, right, "Performing < check");
}
bool LessThan::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type LessThan::data_type() const
{
  return Expression::BOOL;
}


std::string GreaterThanOrEqual::gen_asm()
{
  return binary_operation(MIPS::greater_than_or_equal, this, left, right, "Performing >= check");
}
bool GreaterThanOrEqual::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type GreaterThanOrEqual::data_type() const
{
  return Expression::BOOL;
}


std::string GreaterThan::gen_asm()
{
  return binary_operation(MIPS::greater_than, this, left, right, "Performing > check");
}
bool GreaterThan::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type GreaterThan::data_type() const
{
  return Expression::BOOL;
}


std::string OperatorPlus::gen_asm()
{
  return binary_operation(MIPS::add, this, left, right, "Adding two numbers");
}
bool OperatorPlus::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type OperatorPlus::data_type() const
{
  return Expression::INTEGER;
}


std::string OperatorMinus::gen_asm()
{
  return binary_operation(MIPS::sub, this, left, right, "Subtracting two numbers");
}
bool OperatorMinus::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type OperatorMinus::data_type() const
{
  return Expression::INTEGER;
}


std::string OperatorMult::gen_asm()
{
  return binary_operation(MIPS::mulo, this, left, right, "Multiplying two numbers");
}
bool OperatorMult::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type OperatorMult::data_type() const
{
  return Expression::INTEGER;
}


std::string OperatorDivide::gen_asm()
{
  return binary_operation(MIPS::div, this, left, right, "Dividing two numbers");
}
bool OperatorDivide::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type OperatorDivide::data_type() const
{
  return Expression::INTEGER;
}

std::string OperatorModulus::gen_asm()
{
  return binary_operation(MIPS::rem, this, left, right, "Modding two numbers");
}
bool OperatorModulus::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Expression::Type OperatorModulus::data_type() const
{
  return Expression::INTEGER;
}

namespace
{
  template <typename F>
  std::string unary_operation(F operation, Expression* dest, Expression* src, std::string note)
  {
    std::stringstream s;
    s << src->gen_asm();
    dest->allocate();
    auto dest_reg = dest->result();
    auto src_reg = src->result();
    s << operation(dest_reg,src_reg,note);
    src->release();
    return s.str();
  }
}

/* Unary Operators
   ------------------------------------------------------------------- */
std::string Negation::gen_asm()
{
  return unary_operation(MIPS::bit_flip, this, expr, "Bitwise Negating a number");
}
bool Negation::is_constant() const
{
  return expr->is_constant();
}
Expression::Type Negation::data_type() const
{
  return Expression::BOOL;
}

std::string UnaryMinus::gen_asm()
{
  return unary_operation(MIPS::unary_minus, this, expr, "Taking the negative of a number");
}
bool UnaryMinus::is_constant() const
{
  return expr->is_constant();
}
Expression::Type UnaryMinus::data_type() const
{
  return Expression::INTEGER;
}


std::string FunctionCall::gen_asm()
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


std::string ToChar::gen_asm()
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


std::string ToInt::gen_asm()
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


std::string Predecessor::gen_asm()
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


std::string Successor::gen_asm()
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


/* Literals
   ------------------------------------------------------------------- */
std::string StringLiteral::gen_asm()
{
  allocate();
  std::stringstream s;
  std::string label = "string";

  s << MIPS::data()
    << MIPS::asciiz(label, *literal)
    << MIPS::text()
    << MIPS::la(result_reg, label, "Loading a string's address");
  return s.str();
}

bool StringLiteral::is_constant() const
{
  return true;
}
Expression::Type StringLiteral::data_type() const
{
  return Expression::STRING;
}


std::string CharLiteral::gen_asm() {
  allocate();
  return MIPS::li(result_reg, *literal, "Loading a character");
}

bool CharLiteral::is_constant() const
{
  return true;
}

Expression::Type CharLiteral::data_type() const
{
  return Expression::CHAR;
}

std::string IntLiteral::gen_asm()
{
  allocate();
  return MIPS::li(result_reg, literal, "Loading an integer");
}
bool IntLiteral::is_constant() const
{
  return true;
}
Expression::Type IntLiteral::data_type() const
{
  return Expression::INTEGER;
}

std::string BoolLiteral::gen_asm()
{
  allocate();
  return MIPS::li(result_reg, literal ? 1 : 0, "Loading a boolean");
}
bool BoolLiteral::is_constant() const
{
  return true;
}
Expression::Type BoolLiteral::data_type() const
{
  return Expression::BOOL;
}





std::string LValue::gen_asm()
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

