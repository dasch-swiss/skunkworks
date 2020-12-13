//
// Created by Lukas Rosenthaler on 12.12.20.
//

#include <regex>
#include <sstream>
#include "xsd_integer.h"

static const char file_[] = __FILE__;

namespace xsd {

Integer::Integer(const std::string &val) {
  xsd_type_ = "int";
  if (std::regex_match(val, std::regex("([ ]*)(\\+|\\-)?([0-9]+)([ ]*)"))) {
    val_ = std::atoi(val.c_str());
  } else{
    throw Error(file_, __LINE__, "Not an integer!")
  }
}

std::ostream &Integer::print_to_stream(std::ostream &out_stream) const {
  out_stream << val_;
  return out_stream;
}

Integer::operator std::string() const {
  std::ostringstream ss;
  ss.imbue(std::locale::classic());
  ss << *this;
  return ss.str();
}

}