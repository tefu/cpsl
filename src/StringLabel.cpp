#include <map>
#include <sstream>
#include "StringLabel.hpp"
#include "instructions.hpp"

namespace
{
    std::map<std::string, std::string> labels = {};
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