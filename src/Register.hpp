#ifndef CPSL_REGISTER_HPP
#define CPSL_REGISTER_HPP
#include <vector>
namespace Register {
  int allocate_register();
  void release_register(int reg);
  std::vector<int> clear_all_registers();
  void hog_some_registers(std::vector<int> registers);
};

#endif //CPSL_REGISTER_HPP
