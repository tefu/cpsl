#ifndef CPSL_BLOCK_HPP
#define CPSL_BLOCK_HPP
#include <vector>

#include "ProgramNode.hpp"

struct Program : ProgramNode {
  Program(std::vector<ProgramNode*> fpb, ProgramNode* p)
          : func_or_proc_bodies(fpb), program(p) {}
  std::string gen_asm();
  std::vector<ProgramNode*> func_or_proc_bodies;
  ProgramNode* program;
};

struct Block : ProgramNode {
  Block(std::vector<ProgramNode*>* nodes) : statements(nodes) {}
  std::string gen_asm();
  const std::vector<ProgramNode*>* statements;
};

struct FunctionBlock : ProgramNode {
  FunctionBlock(std::string func_label, ProgramNode* b)
          : block(b), function_label(func_label) {}
  std::string gen_asm();
  ProgramNode* block;
  std::string function_label;
};

#endif //CPSL_BLOCK_HPP
