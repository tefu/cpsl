#include <sstream>
#include <iostream>
#include "Block.hpp"

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