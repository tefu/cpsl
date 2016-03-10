#include <map>
#include <sstream>
#include "StringLabel.hpp"
#include "instructions.hpp"

namespace
{
  std::map<std::string, std::string> labels = {};
  int string_label_count = 0;
  int branch_label_count = 0;
  int function_label_count = 0;

  std::string get_unique_label(std::string name, int& count)
  {
    std::stringstream s;
    s << name << count;
    count++;
    return s.str();
  }

}

void StringLabel::store_label(std::string label, std::string literal_string)
{
    labels.emplace(label, literal_string);
}

std::string StringLabel::print_labels()
{
    std::stringstream s;
    s << MIPS::data();
    for(auto &pair: labels)
    {
        auto label = pair.first;
        auto data = pair.second;
        s << MIPS::asciiz(label, data);
    }
    return s.str();
}

std::string StringLabel::get_unique_string_label()
{
  return get_unique_label("string_", string_label_count);
}

std::string StringLabel::get_unique_control_label()
{
  return get_unique_label("branch_", branch_label_count);
}


std::string StringLabel::get_unique_function_label()
{
  return get_unique_label("function_", function_label_count);
}
