//
// Created by Lukas Rosenthaler on 27.11.20.
//

#ifndef SKUNKWORKS_LANG_STRING_H
#define SKUNKWORKS_LANG_STRING_H

#include <unordered_map>
#include <string>
namespace xsd {

enum Language {
  en,
  de,
  fr,
  it,
  rm
};

class LangString {
 public:
  LangString(Language lang, const std::string text);

  std::string operator[](Language lang);

  void remove(Language lang);
};
}

#endif //SKUNKWORKS_LANG_STRING_H
