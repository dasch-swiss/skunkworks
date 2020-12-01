//
// Created by Lukas Rosenthaler on 01.12.20.
//

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_XSD_ANY_URI_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_XSD_ANY_URI_H_

#include <string>
#include <regex>

#include "xsd_string.h"

namespace xsd {

class AnyUri : public String {
 private:
  inline bool validate_uri(const std::string strval) const {
    std::regex url_regex(
        R"(^(([^:\/?#]+):)?(//([^\/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)",
        std::regex::extended);
    std::smatch url_match_result;
    return std::regex_match(strval, url_match_result, url_regex);
  }

 public:
  inline AnyUri(const std::string strval) : String(strval) {
    if (!this->validate_uri(strval_)) throw Error(__FILE__, __LINE__, "Invalid IRI!");
  }

  inline AnyUri(const std::string strval, const StringRestriction &restriction) : String(strval, restriction) {
    if (!this->validate_uri(strval_)) throw Error(__FILE__, __LINE__, "Invalid IRI!");
  }

  inline AnyUri(const std::string &strval, const std::vector<StringRestriction> &restrictions) : String(strval,restrictions) {
    if (!this->validate_uri(strval_)) throw Error(__FILE__, __LINE__, "Invalid IRI!");
  }
};

}

#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_ANY_URI_H_
