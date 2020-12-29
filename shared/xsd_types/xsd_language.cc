//
// Created by Lukas Rosenthaler on 18.12.20.
//

#include "xsd_language.h"

namespace xsd {

const std::set<std::string> Language::langs = std::set<std::string>({
  "ba", "bg", "ca", "co", "cs", "da", "de", "el", "en", "eo", "es", "et", "eu", "fa", "fi", "fo", "fr", "ga", "he",
  "hi", "hr", "hu", "it", "ja", "ko", "ku", "la", "lb", "lt", "lv", "mn", "mt", "my", "nl", "no", "pl",
  "pt", "ro", "rm", "ru", "sc", "sk", "sl", "sq", "sv", "ta", "uk", "yi", "zh"
});

Language::Language() : String(std::make_shared<RestrictionEnumeration>(langs)) {}

Language::Language(const std::string &strval)
: String(strval, std::make_shared<RestrictionEnumeration>(langs)) {}

}