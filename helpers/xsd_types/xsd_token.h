//
// Created by Lukas Rosenthaler on 12.12.20.
//

#include "xsd_normalized_string.h"

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_TOKEN_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_TOKEN_H_

namespace xsd {

class Token : public NormalizedString {
  /*!
   * Implements the xsd::token data type (see https://www.w3.org/TR/xmlschema-2/#token)
   */
 public:
  /*!
   * Default constructor for xsd:token
   */
  inline Token() { xsd_type_ = "token"; };

  /*!
   * Constructor taking one restriction (shared_ptr) as parameter
   * @param restriction
   */
  inline explicit Token(const std::shared_ptr<Restriction> &restriction) : Token() {
    restrictions_.push_back(restriction);
  }

  inline explicit Token(const std::vector<std::shared_ptr<Restriction>> &restrictions) : Token() {
    restrictions_ = restrictions;
  }

  /*!
   * Constructor taking a std::string a parameter
   * @param strval
   */
  explicit Token(const std::string &strval);

  /*!
   * Constructor taking a std::string and a restriction (shared_ptr) as parameter
   * @param strval
   * @param restriction
   */
  Token(const std::string &strval, const std::shared_ptr<Restriction> &restriction);

  /*!
   * Constructor taking a std::string and a vector of restrictions (shared_ptr's)
   * @param strval
   * @param restrictions
   */
  Token(const std::string &strval, const std::vector<std::shared_ptr<Restriction>> &restrictions);

  void set(const std::string &strval) override;

  Token &operator=(const std::string &strval) override;

 protected:
  void clean();

};

}


#endif //SKUNKWORKS_HELPERS_XSD_TYPES_TOKEN_H_
