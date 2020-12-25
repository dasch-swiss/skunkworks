//
// Created by Lukas Rosenthaler on 27.11.20.
//

#ifndef SKUNKWORKS_LANG_STRING_H
#define SKUNKWORKS_LANG_STRING_H

#include <unordered_map>
#include <string>
#include <vector>

#include "xsd_restriction.h"
#include "xsd_string.h"
#include "xsd_language.h"

namespace xsd {

class LangString {
 public:

  LangString() = default;

  LangString(const Language &lang, const xsd::String &text);

  LangString(const std::string &lang, const xsd::String &text);

  LangString(const LangString &ls) = default;

  xsd::String &operator[](const std::string  &lang);

  xsd::String &operator[](const Language &lang);

  void add(const Language &language, const xsd::String &text);

  void remove(const Language &lang);

 private:
  std::unordered_map<std::string, xsd::String> lang_string_;

};
}

#endif //SKUNKWORKS_LANG_STRING_H
