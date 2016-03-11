#include "Register.hpp"
#include <set>

namespace
{
  std::set<int> registers_taken = {};
  const int starting_register=8;
}

int Register::allocate_register()
{
  int winning_register = starting_register;
  while(registers_taken.find(winning_register) != registers_taken.end())
  {
    winning_register++;
  }
  registers_taken.insert(winning_register);

  return winning_register;
}

void Register::release_register(int reg)
{
  registers_taken.erase(reg);
}

std::vector<int> Register::clear_all_registers()
{
  std::vector<int> cleared_registers;
  for(auto reg: registers_taken)
  {
    cleared_registers.push_back(reg);
  }
  registers_taken.clear();
  return cleared_registers;
}

void Register::hog_some_registers(std::vector<int> registers)
{
  for(auto reg: registers)
  {
    registers_taken.insert(reg);
  }
}