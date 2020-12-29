//
// Created by Lukas Rosenthaler on 12.12.20.
//

#include <regex>
#include <sstream>
#include "xsd_integer.h"

static const char file_[] = __FILE__;

namespace xsd {


Integer::Integer(const std::string &strval) {
  xsd_type_ = "integer";
  val_ = 0;
  parse(strval);
}

Integer::Integer(int64_t val, const std::shared_ptr<Restriction> &restriction) : Integer(val) {
    restrictions_.push_back(restriction);
    enforce_restrictions();
};

Integer::Integer(int64_t val, const std::vector<std::shared_ptr<Restriction>> &restrictions) : Integer(val) {
    restrictions_ = restrictions;
    enforce_restrictions();
};

Integer::Integer(const std::string &val, const std::shared_ptr<Restriction> &restriction) : Integer(val) {
  restrictions_.push_back(restriction);
  enforce_restrictions();
}

Integer::Integer(const std::string &val, const std::vector<std::shared_ptr<Restriction>> &restrictions) : Integer(val) {
  restrictions_ = restrictions;
  enforce_restrictions();
}

void Integer::set(const std::string &strval) {
  parse(strval);
  enforce_restrictions();
}

Integer &Integer::operator=(const std::string &strval) {
  set(strval);
  return *this;
}

Integer &Integer::operator=(int64_t val) {
  val_ = val;
  enforce_restrictions();
  return *this;
}

bool Integer::operator==(const Integer &other) const  {
  return val_ == other.val_;
}

void Integer::parse(const std::string &strval) {
  val_ = 0;
  if (std::regex_match(strval, std::regex("([ ]*)(\\+|\\-)?([0-9]+)([ ]*)"))) {
    val_ = std::stoll(strval);
  } else {
    throw Error(file_, __LINE__, "Not an integer!");
  }
}


std::ostream &Integer::print_to_stream(std::ostream &out_stream) const {
  out_stream.imbue(std::locale::classic());
  out_stream << val_;
  return out_stream;
}

}

namespace std {

template<> struct hash<xsd::Integer> {
  std::size_t  operator()(xsd::Integer const &value) const noexcept {
    return std::hash<int64_t>{}(value.getVal());
  }
};

}