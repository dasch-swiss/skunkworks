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

LangString::LangString(const std::string &lang, const std::string &text) {
  lang_string_[lang] = xsd::String(text);
}

xsd::String &LangString::operator[](const Language &lang) {
  return lang_string_[static_cast<std::string>(lang)];
}

xsd::String &LangString::operator[](const std::string &lang) {
  return lang_string_[lang];
}

const xsd::String LangString::get(const Language &lang) {
  try {
    return lang_string_.at(lang);
  } catch (const std::out_of_range &err) {
    for (const auto &s: lang_string_) {
      if (!s.second.empty()) return s.second;
    }
  }
  return xsd::String();
}

void LangString::add(const Language &lang, const xsd::String &text) {
  lang_string_[static_cast<std::string>(lang)] = text;
}

void LangString::remove(const Language &lang) {
  lang_string_.erase(static_cast<std::string>(lang));
}
}