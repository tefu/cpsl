#ifndef CPSL_PROGRAMNODE_H
#define CPSL_PROGRAMNODE_H
#include <string>

struct ProgramNode
{
  virtual std::string gen_asm() const=0;
};

#endif //CPSL_PROGRAMNODE_H
