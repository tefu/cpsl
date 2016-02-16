#ifndef CPSL_BLOCK_HPP
#define CPSL_BLOCK_HPP
#include <vector>

#include "ProgramNode.hpp"


struct Block : ProgramNode {
  Block(std::vector<ProgramNode*>* nodes) : statements(nodes) {}
  std::string gen_asm();
  const std::vector<ProgramNode*>* statements;
};


#endif //CPSL_BLOCK_HPP
