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
Type LogicalOr::data_type() const
{
  return Boolean{};
}


std::string LogicalAnd::gen_asm()
{
  return binary_operation(MIPS::logical_and, this, left, right, "Performing logical AND");
}
bool LogicalAnd::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Type LogicalAnd::data_type() const
{
  return Boolean{};
}


std::string Equality::gen_asm()
{
  return binary_operation(MIPS::equality, this, left, right, "Performing equality check");
}
bool Equality::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Type Equality::data_type() const
{
  return Boolean{};
}


std::string Inequality::gen_asm()
{
  return binary_operation(MIPS::inequality, this, left, right, "Performing inequality check");
}
bool Inequality::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Type Inequality::data_type() const
{
  return Boolean{};
}


std::string LessThanOrEqual::gen_asm()
{
  return binary_operation(MIPS::less_than_or_equal, this, left, right, "Performing <= check");
}
bool LessThanOrEqual::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Type LessThanOrEqual::data_type() const
{
  return Boolean{};
}


std::string LessThan::gen_asm()
{
  return binary_operation(MIPS::less_than, this, left, right, "Performing < check");
}
bool LessThan::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Type LessThan::data_type() const
{
  return Boolean{};
}


std::string GreaterThanOrEqual::gen_asm()
{
  return binary_operation(MIPS::greater_than_or_equal, this, left, right, "Performing >= check");
}
bool GreaterThanOrEqual::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Type GreaterThanOrEqual::data_type() const
{
  return Boolean{};
}


std::string GreaterThan::gen_asm()
{
  return binary_operation(MIPS::greater_than, this, left, right, "Performing > check");
}
bool GreaterThan::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Type GreaterThan::data_type() const
{
  return Boolean{};
}


std::string OperatorPlus::gen_asm()
{
  return binary_operation(MIPS::add, this, left, right, "Adding two numbers");
}
bool OperatorPlus::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Type OperatorPlus::data_type() const
{
  return Integer{};
}


std::string OperatorMinus::gen_asm()
{
  return binary_operation(MIPS::sub, this, left, right, "Subtracting two numbers");
}
bool OperatorMinus::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Type OperatorMinus::data_type() const
{
  return Integer{};
}


std::string OperatorMult::gen_asm()
{
  return binary_operation(MIPS::mulo, this, left, right, "Multiplying two numbers");
}
bool OperatorMult::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Type OperatorMult::data_type() const
{
  return Integer{};
}


std::string OperatorDivide::gen_asm()
{
  return binary_operation(MIPS::div, this, left, right, "Dividing two numbers");
}
bool OperatorDivide::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Type OperatorDivide::data_type() const
{
  return Integer{};
}

std::string OperatorModulus::gen_asm()
{
  return binary_operation(MIPS::rem, this, left, right, "Modding two numbers");
}
bool OperatorModulus::is_constant() const
{
  return is_binary_operation_constant(left, right);
}
Type OperatorModulus::data_type() const
{
  return Integer{};
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
Type Negation::data_type() const
{
  return Boolean{};
}

std::string UnaryMinus::gen_asm()
{
  return unary_operation(MIPS::unary_minus, this, expr, "Taking the negative of a number");
}
bool UnaryMinus::is_constant() const
{
  return expr->is_constant();
}
Type UnaryMinus::data_type() const
{
  return Integer{};
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
Type FunctionCall::data_type() const
{
  // TODO: look up type declaration.
  return Integer{};

}


std::string ToChar::gen_asm()
{
  return expr->gen_asm();
}
bool ToChar::is_constant() const
{
  return expr->is_constant();
}
Type ToChar::data_type() const
{
  return Character{};
}


std::string ToInt::gen_asm()
{
  return expr->gen_asm();
}
bool ToInt::is_constant() const
{
  return expr->is_constant();
}
Type ToInt::data_type() const
{
  return Integer{};
}

namespace
{
  std::string add_or_flip(Expression* dest, Expression* src, int to_add, std::string int_note)
  {
    std::stringstream s;
    s << src->gen_asm();
    dest->allocate();
    s << ((src->data_type().type() == Type::INTEGER) ?
         MIPS::addi(dest->result(), src->result(), to_add, int_note) :
         MIPS::bit_flip(dest->result(), src->result(), "Flipping a boolean"));

    src->release();
    return s.str();
  }
}


std::string Predecessor::gen_asm()
{
  return add_or_flip(this, expr, -1, "Decrementing an integer");
}
bool Predecessor::is_constant() const
{
  return expr->is_constant();
}
Type Predecessor::data_type() const
{
  return expr->data_type();
}


std::string Successor::gen_asm()
{
  return add_or_flip(this, expr, 1, "Incrementing an integer");
}
bool Successor::is_constant() const
{
  return expr->is_constant();
}
Type Successor ::data_type() const
{
  return expr->data_type();
}

namespace
{
  int label_count = 0;

  std::string get_unique_string_label()
  {
    std::stringstream s;
    s << "string_friend_" << label_count;
    label_count++;
    return s.str();
  }
}

/* Literals
   ------------------------------------------------------------------- */
std::string StringLiteral::gen_asm()
{
  allocate();
  std::stringstream s;
  auto label = get_unique_string_label();

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
Type StringLiteral::data_type() const
{
  return StringConstant{};
}


std::string CharLiteral::gen_asm() {
  allocate();
  return MIPS::li(result_reg, *literal, "Loading a character");
}

bool CharLiteral::is_constant() const
{
  return true;
}

Type CharLiteral::data_type() const
{
  return Character{};
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
Type IntLiteral::data_type() const
{
  return Integer{};
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
Type BoolLiteral::data_type() const
{
  return Boolean{};
}





std::string LValue::gen_asm()
{
  return "";
}
bool LValue::is_constant() const
{
  return false;
}

Type LValue::data_type() const
{
  return Integer{};
}

