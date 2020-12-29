//
// Created by Lukas Rosenthaler on 18.12.20.
//

#include <regex>

#include "xsd_q_name.h"
#include "xsd_error.h"
#include "splitter.h"

static const char file_[] = __FILE__;

namespace xsd {

QName::QName(const std::string &strval) : QName() {
  parse(strval);
  enforce_restrictions();
}

QName::QName(const std::string &strval, const std::shared_ptr<Restriction> &restriction) : QName(strval) {
  restrictions_.push_back(restriction);
  enforce_restrictions();
}

QName::QName(const std::string &strval, const std::vector<std::shared_ptr<Restriction>> &restrictions) : QName(strval) {
  restrictions_ = restrictions;
  enforce_restrictions();
}

QName &QName::operator=(const std::string &strval) {
  set(strval);
  enforce_restrictions();
  return *this;
}

void QName::set(const std::string &strval) {
  parse(strval);
  enforce_restrictions();
}

std::ostream &QName::print_to_stream(std::ostream &out_stream) const {
  if (!prefix_.empty()) out_stream << prefix_ << ":";
  out_stream << name_;
  return out_stream;
}

void QName::parse(const std::string &strval) {
  SplitResult split_result = split_first(strval, ':');
  if (split_result.success) {
    prefix_ = split_result.first;
    name_ = split_result.second;
  } else {
    name_ = strval;
  }
  if (!prefix_.empty() && !std::regex_match(prefix_, std::regex(R"(([a-zA-Z_\xC0-\xD6\xD8-\xF6])([a-zA-Z0-9_·\-\xC0-\xD6\xD8-\xF6])+)"))) {
    throw Error(file_, __LINE__, "Prefix contains non-valid characters!");
  }
  if (!std::regex_match(name_, std::regex(R"(([a-zA-Z_\xC0-\xD6\xD8-\xF6])([a-zA-Z0-9_·\-\xC0-\xD6\xD8-\xF6])+)"))) {
    throw Error(file_, __LINE__, "Name contains non-valid characters!");
  }
}


}