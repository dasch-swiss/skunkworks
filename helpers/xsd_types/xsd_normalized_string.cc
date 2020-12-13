//
// Created by Lukas Rosenthaler on 12.12.20.
//

#include "xsd_normalized_string.h"

namespace xsd {

std::string NormalizedString::normalize(const std::string &strval) {
  std::string tmpstr(strval.length(), ' ');
  for (int i = 0; i < strval.length(); ++i) {
    if (strval[i] == '\t' || strval[i] == '\r' || strval[i] == '\n') {
      tmpstr[i] = ' ';
    } else {
      tmpstr[i] = strval[i];
    }
  }
  return tmpstr;
}


NormalizedString::NormalizedString(const std::string &strval) : String(strval) {
  xsd_type_ = "normalizedString";
  strval_ = normalize(strval);
}

NormalizedString::NormalizedString(const std::string &strval, const std::shared_ptr<StringRestriction> restriction) : NormalizedString(strval) {
  restrictions_.push_back(restriction);
  validate();
}

NormalizedString::NormalizedString(const std::string &strval, const std::vector<std::shared_ptr<StringRestriction>> &restrictions) : NormalizedString(strval) {
  xsd_type_ = "normalizedString";
  restrictions_ = restrictions;
  validate();
}


void NormalizedString::set(const std::string &strval) {
  strval_ = normalize(strval);
  validate();
}

}