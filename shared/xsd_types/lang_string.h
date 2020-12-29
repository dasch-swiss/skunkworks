//
// Created by Lukas Rosenthaler on 27.11.20.
//

#ifndef SKUNKWORKS_LANG_STRING_H
#define SKUNKWORKS_LANG_STRING_H

#include <unordered_map>
#include <string>
#include <vector>
#include <iterator>

#include "xsd_restriction.h"
#include "xsd_string.h"
#include "xsd_language.h"

namespace xsd {

class LangString {
 private:
  typedef std::unordered_map<std::string, xsd::String> LangStringMap;

 public:

  LangString() = default;

  LangString(const Language &lang, const xsd::String &text);

  LangString(const std::string &lang, const std::string &text);

  LangString(const LangString &lang_string) = default;

  xsd::String &operator[](const std::string &lang);

  xsd::String &operator[](const Language &lang);

  const xsd::String get(const Language &lang);

  const xsd::String get(const std::string &lang);

  void add(const Language &language, const xsd::String &text);

  void remove(const Language &lang);

  typedef LangStringMap::iterator iterator;
  typedef LangStringMap::const_iterator const_iterator;
  iterator begin() { return lang_string_.begin(); }
  iterator end() { return lang_string_.end(); }

 private:
  LangStringMap lang_string_;

};
}

#endif //SKUNKWORKS_LANG_STRING_H
