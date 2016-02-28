#ifndef CPSL_REGISTER_HPP
#define CPSL_REGISTER_HPP

namespace Register {
  int allocate_register();
  void release_register(int reg);
};

#endif //CPSL_REGISTER_HPP
