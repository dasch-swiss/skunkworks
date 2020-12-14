//
// Created by Lukas Rosenthaler on 12.12.20.
//

#include <regex>
#include <sstream>
#include "xsd_integer.h"

static const char file_[] = __FILE__;

namespace xsd {

int64_t Integer::parse(const std::string &strval) {
  int64_t val = 0;
  if (std::regex_match(strval, std::regex("([ ]*)(\\+|\\-)?([0-9]+)([ ]*)"))) {
    val = std::atoi(strval.c_str());
  } else{
    throw Error(file_, __LINE__, "Not an integer!");
  }
  return val;
}

Integer::Integer(const std::string &strval) {
  xsd_type_ = "int";
  val_ = parse(strval);
}

void Integer::set(const std::string &strval) {
  val_ = parse(strval);
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