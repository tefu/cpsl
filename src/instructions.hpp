#ifndef CPSL_INSTRUCTIONS_H
#define CPSL_INSTRUCTIONS_H

#include <sstream>
#include <string>

struct instruction {
  std::string op_code;
  int src1;
  int src2;
  int dest;
};

namespace MIPS {
  std::string push_on_stack(std::string);
  std::string pop_off_stack(std::string);
  std::string system_call(int);
  std::string print_string(std::string);
  std::string print_int(int);
}


#endif //CPSL_INSTRUCTIONS_H
