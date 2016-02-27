#ifndef CPSL_INSTRUCTIONS_H
#define CPSL_INSTRUCTIONS_H

#include <sstream>
#include <string>
#include "Expression.hpp"

namespace MIPS {
  const int ZERO=0;
  const int AT=1;
  const int V0=2;
  const int V1=3;
  const int A0=4;
  const int A1=5;
  const int A2=6;
  const int A3=7;
  const int GP=28;
  const int SP=29;

  std::string li(int, int, std::string);
  std::string li(int, std::string, std::string);
  std::string la(int, std::string, std::string);
  std::string add(int, int, int, std::string);
  std::string addi(int, int, int, std::string);
  std::string sub(int, int, int, std::string);
  std::string subi(int, int, int, std::string);
  std::string beq(int, int, std::string, std::string);
  std::string bne(int, int, std::string, std::string);
  std::string blt(int, int, std::string, std::string);
  std::string bgt(int, int, std::string, std::string);
  std::string mulo(int, int, int, std::string);
  std::string div(int, int, int, std::string);
  std::string rem(int, int, int, std::string);
  std::string logical_or(int, int, int, std::string);
  std::string logical_and(int, int, int, std::string);
  std::string equality(int, int, int, std::string);
  std::string inequality(int, int, int, std::string);
  std::string less_than_or_equal(int, int, int, std::string);
  std::string less_than(int, int, int, std::string);
  std::string greater_than_or_equal(int, int, int, std::string);
  std::string greater_than(int, int, int, std::string);

  std::string bit_flip(int, int, std::string);
  std::string unary_minus(int, int, std::string);

  std::string branch(std::string, std::string);
  std::string store_word(int, int, int, std::string);
  std::string load_word(int, int, int, std::string);

  std::string push_on_stack(int);
  std::string pop_off_stack(int);
  std::string system_call(int);

  std::string data();
  std::string asciiz(std::string, std::string);
  std::string text();

}


#endif //CPSL_INSTRUCTIONS_H
