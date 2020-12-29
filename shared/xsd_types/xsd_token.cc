//
// Created by Lukas Rosenthaler on 12.12.20.
//

#include "xsd_token.h"

namespace xsd {

Token::Token(const std::string &strval) : NormalizedString(strval) {
  xsd_type_ = "token";
  clean();
}

Token::Token(const std::string &strval, const std::shared_ptr<Restriction> &restriction) : Token(strval) {
  restrictions_.push_back(restriction);
  enforce_restrictions();
}

Token::Token(const std::string &strval, const std::vector<std::shared_ptr<Restriction>> &restrictions) : Token(strval) {
  restrictions_ = restrictions;
  enforce_restrictions();
}


void Token::clean() {
  std::regex re("([ ]){2,}");
  strval_ = std::regex_replace(strval_, re, " ");
  std::regex re2("(^[ ]+)");
  strval_ = std::regex_replace(strval_, re2, "");
  std::regex re3("([ ]+$)");
  strval_ = std::regex_replace(strval_, re3, "");
}

void Token::set(const std::string &strval) {
  strval_ = normalize(strval);
  clean();
  enforce_restrictions();
}

Token &Token::operator= (const std::string &strval) {
  set(strval);
  return *this;
}

}