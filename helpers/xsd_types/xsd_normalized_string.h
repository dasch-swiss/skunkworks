//
// Created by Lukas Rosenthaler on 12.12.20.
//

#include "xsd_string.h"

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_NORMALIZED_STRING_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_NORMALIZED_STRING_H_

namespace xsd {

class NormalizedString : public String {
  /*!
   * Implements a xsd:normalizedString where "\n", "\t", "\r" are replaced by blanks. This replacement
   * is automaticall been done on construction of an instance or when assigning a value!
   */
 public:
  /*!
   * Default constructor for empty string
   */
  inline NormalizedString() { xsd_type_ = "normalizedString"; };

  /*!
   * Constructor with just a restriction (shared_ptr) as parameter
   * @param restriction
   */
  inline explicit NormalizedString(const std::shared_ptr<Restriction> &restriction) : NormalizedString() {
    restrictions_.push_back(restriction);
  }

  /*!
   * Constructor with a vector of restrictions (shared_ptr) as parameter
   * @param restrictions
   */
  inline explicit NormalizedString(const std::vector<std::shared_ptr<Restriction>> &restrictions) : NormalizedString() {
    restrictions_ = restrictions;
  }

  /*!
   * Constructor which takes std::string as parameter
   * @param strval
   */
  explicit NormalizedString(const std::string &strval);

  /*!
   * Constructor which takes a string and a shared pointer to a restriction.
   *
   * Please note that the restriction has to be passed as shared pointer:
   * @param strval
   * @param restriction
   */
  NormalizedString(const std::string &strval, const std::shared_ptr<Restriction> &restriction);

  /*!
   * Constructor taking a std::string and a vector of restrictions (shared_ptr's)
   * @param strval
   * @param restrictions
   */
  NormalizedString(const std::string &strval, const std::vector<std::shared_ptr<Restriction>> &restrictions);

  void set(const std::string &strval) override;

  inline NormalizedString &operator=(const std::string &strval) override {
    set(strval);
    return *this;
  }

 protected:
  std::string normalize(const std::string &strval);

};


}

#endif //SKUNKWORKS_HELPERS_XSD_TYPES_NORMALIZED_STRING_H_
