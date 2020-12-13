//
// Created by Lukas Rosenthaler on 12.12.20.
//

#include "xsd_string.h"

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_NORMALIZED_STRING_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_NORMALIZED_STRING_H_

namespace xsd {

class NormalizedString : public String {
  /*!
   * Implements a xsd:normalizedString where "\n", "\t", "\r" are replaced by blanks
   */
 public:
  /*!
   * Default constructor for empty string
   */
  inline NormalizedString() {};

  /*!
   * Constructor which takes std::string as parameter
   * @param strval
   */
  NormalizedString(const std::string &strval);

  /*!
   * Constructor which takes a string and a shared pointer to a restriction.
   *
   * Please note that the restriction has to be passed as shared pointer:
   *  ```
   *
   *  ```
   * @param strval
   * @param restriction
   */
  NormalizedString(const std::string &strval, const std::shared_ptr<StringRestriction> restriction);

  NormalizedString(const std::string &strval, const std::vector<std::shared_ptr<StringRestriction>> &restrictions);

  void set(const std::string &strval) override ;

 private:
  std::string normalize(const std::string &strval);

};


}

#endif //SKUNKWORKS_HELPERS_XSD_TYPES_NORMALIZED_STRING_H_
