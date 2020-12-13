//
// Created by Lukas Rosenthaler on 12.12.20.
//

#include "xsd_token.h"

namespace xsd {

Token::Token(const std::string &strval) : NormalizedString(strval) {
  xsd_type_ = "token";
  std::regex re("([ ]){2,}");
  strval_ = std::regex_replace(strval_, re, " ");
  std::regex re2("(^[ ]+)");
  strval_ = std::regex_replace(strval_, re2, "");
  std::regex re3("([ ]+$)");
  strval_ = std::regex_replace(strval_, re3, "");
}

}