#include <sstream>
#include <iostream>
#include <string>
#include "Block.hpp"
#include "instructions.hpp"
#include "StringLabel.hpp"

std::string Program::gen_asm()
{
  std::stringstream s;
  auto global_label = std::string("global_address");
  s << MIPS::text()
  << ".globl main\n"
  << MIPS::la(MIPS::GP, global_label, "Initializing the global pointer");

  s << MIPS::label("main","");
  s << program->gen_asm();
  s << MIPS::system_call(10);

  for (auto &body: func_or_proc_bodies)
  {
    if (body != nullptr)
      s << body->gen_asm();
  }


  s << StringLabel::print_labels();
  s << ".align 2\n";
  s << MIPS::label(global_label, "");

  return s.str();
}

std::string Block::gen_asm()
{
  std::stringstream s;

  for(auto &statement: *statements)
  {
    if (statement != nullptr)
    {
      s << statement->gen_asm();
    }
  }

  return s.str();
}


std::string FunctionBlock::gen_asm()
{
  std::stringstream s;
  s << MIPS::label(function_label, "");
  s << block->gen_asm();
  s << MIPS::jr(MIPS::RA, "Default return from function");

  return s.str();
}
