#include <sstream>
#include <iostream>
#include <string>
#include "Block.hpp"
#include "instructions.hpp"
#include "StringLabel.hpp"

std::string Block::gen_asm()
{
  std::stringstream s;
  auto global_label = std::string("global_address");
  s << MIPS::text()
    << ".globl main\n"
    << "main:\n"
    << MIPS::la(MIPS::GP, global_label, "Initializing the global pointer");

  for(auto &statement: *statements)
  {
    if (statement != nullptr)
    {
      s << statement->gen_asm();
    }
  }

  s << StringLabel::print_labels();
  s << global_label << ":\n";

  return s.str();
}
