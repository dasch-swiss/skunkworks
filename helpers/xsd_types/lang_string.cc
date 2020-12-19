//
// Created by Lukas Rosenthaler on 27.11.20.
//
#include <stdexcept>
#include <string>
#include <memory>

#include "lang_string.h"

namespace xsd {

LangString::LangString(const Language &lang, const xsd::String &text) {
  lang_string_[static_cast<std::string>(lang)] = text;
}

LangString::LangString(const std::string &lang, const xsd::String &text) {
  lang_string_[lang] = text;
}

xsd::String &LangString::operator[](const Language &lang) {
  return lang_string_[static_cast<std::string>(lang)];
}

xsd::String &LangString::operator[](const std::string &lang) {
  return lang_string_[lang];
}

void LangString::add(const Language &lang, const xsd::String &text) {
  lang_string_[static_cast<std::string>(lang)] = text;
}

void LangString::remove(const Language &lang) {
  lang_string_.erase(static_cast<std::string>(lang));
}
}