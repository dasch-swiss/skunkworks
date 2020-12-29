//
// Created by Lukas Rosenthaler on 18.12.20.
//

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_XSD_LANGUAGE_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_XSD_LANGUAGE_H_

#include <string>
#include "shared/xsd_types/xsd_restriction.h"
#include "shared/xsd_types/xsd_string.h"


namespace xsd {

class Language : public String {
 public:
  Language();

  explicit Language(const std::string &strval);

 private:
  const static std::set<std::string> langs;

};



}
#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_LANGUAGE_H_
