//
// Created by Lukas Rosenthaler on 14.12.20.
//
static const char file_[] = __FILE__;

#include <string>
#include <sstream>

#include "xsd_error.h"
#include "xsd_decimal.h"

namespace xsd {

void Decimal::parse(const std::string &strval) {
  dval_ = 0.0;
  if (std::regex_match(strval.c_str(), std::regex(R"(^(\+|\-)?([0-9]+)?(\.[0-9]+)?([e|E][\+\-]?[0-9]+)?$)"))) {
    dval_ = std::stod(strval);
  } else {
    throw Error(file_, __LINE__, "Not an integer!");
  }
}

Decimal::Decimal(double dval, const std::shared_ptr<Restriction> &restriction) : Decimal(dval) {
  restrictions_.push_back(restriction);
  enforce_restrictions();
}

Decimal::Decimal(double dval, const std::vector<std::shared_ptr<Restriction>> &restrictions) : Decimal(dval) {
  restrictions_ = restrictions;
  enforce_restrictions();
}

Decimal::Decimal(const std::string &strval, const std::shared_ptr<Restriction> &restriction) : Decimal(strval) {
  restrictions_.push_back(restriction);
  enforce_restrictions();
}

Decimal::Decimal(const std::string &strval, const std::vector<std::shared_ptr<Restriction>> &restrictions) {
  restrictions_ = restrictions;
  enforce_restrictions();
}

void Decimal::set(const std::string &strval) {
  parse(strval);
  enforce_restrictions();
}

Decimal &Decimal::operator=(const std::string &strval) {
  set(strval);
  return *this;
}

Decimal &Decimal::operator=(double dval) {
  dval_ = dval;
  enforce_restrictions();
  return *this;
}

bool Decimal::operator==(const Decimal &other) const {
  return dval_ == other.dval_;
}

std::ostream &Decimal::print_to_stream(std::ostream &out_stream) const {
  out_stream.imbue(std::locale::classic());
  out_stream << dval_;
  return out_stream;
}

}

