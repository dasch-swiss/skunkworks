//
// Created by Lukas Rosenthaler on 14.12.20.
//
static const char file_[] = __FILE__;

#include <string>
#include <sstream>

#include "xsd_error.h"
#include "xsd_decimal.h"

namespace xsd {

double Decimal::parse(const std::string &strval) {
  if (std::regex_match(strval.c_str(), std::regex("^(\\+|\\-)?([0-9]+)?(\\.[0-9]+)?([e|E][\\+\\-]?[0-9]+)?$"))) {
    return std::stod(strval);
  } else {
    throw Error(file_, __LINE__, "Not an integer!");
  }
}

Decimal::Decimal(double dval, const std::shared_ptr<Restriction> restriction) : Decimal(dval) {
  restrictions_.push_back(restriction);
  validate();
}

Decimal::Decimal(double dval, const std::vector<std::shared_ptr<Restriction>> &restrictions) : Decimal(dval) {
  restrictions_ = restrictions;
  validate();
}

Decimal::Decimal(const std::string strval, const std::shared_ptr<Restriction> restriction) : Decimal(strval) {
  restrictions_.push_back(restriction);
  validate();
}

std::ostream &Decimal::print_to_stream(std::ostream &out_stream) const {
  out_stream << dval_;
  return out_stream;
}

Decimal::operator std::string() const {
  std::ostringstream ss;
  ss.imbue(std::locale::classic());
  ss << *this;
  return ss.str();
}

void Decimal::set(const std::string &strval) {
  dval_ = parse(strval);
  validate();
}


}