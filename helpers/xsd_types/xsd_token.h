//
// Created by Lukas Rosenthaler on 12.12.20.
//

#include "xsd_normalized_string.h"

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_TOKEN_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_TOKEN_H_

namespace xsd {

class Token : public NormalizedString {
 public:
  inline Token() { xsd_type_ = "token"; };

  Token(const std::string &strval);

  inline Token(const std::string &strval, const std::vector<StringRestriction> &restrictions) : Token(strval) {
    xsd_type_ = "token";
    for (int i = 0; i < restrictions.size(); i++) {
      if (!restrictions[i].validate(strval_)) throw Error(__FILE__, __LINE__, "xsd:string did not pass validation!");
    }
  }

};

}


#endif //SKUNKWORKS_HELPERS_XSD_TYPES_TOKEN_H_
