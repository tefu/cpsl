#ifndef CPSL_STRINGLABEL_HPP
#define CPSL_STRINGLABEL_HPP
#include <string>

namespace StringLabel {
  void store_label(std::string, std::string);
  std::string print_labels();
  std::string get_unique_string_label();
  std::string get_unique_control_label();
};


#endif //CPSL_STRINGLABEL_HPP
