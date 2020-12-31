//
// Created by Ivan Subotic on 23/12/2020.
//

#ifndef SKUNKWORKS_ENTITIES_USER_PASSWORD_H_
#define SKUNKWORKS_ENTITIES_USER_PASSWORD_H_

#include <string>
#include "shared/xsd_types/xsd.h"

namespace admin::user {

class Password {
 public:
  /*!
   * Default constructor setting empty value. Sets any Restrictions.
   */
  Password();

  /*!
   * Constructor taking a std::string as parameter
   * @param value
   */
  inline explicit Password(const std::string &value) : Password() { value_ = value; }

  /*!
   * Constructor taking a xsd::String as parameter.
   * @param value
   */
  inline explicit Password(const xsd::String &value) : Password() { value_ = value; };

  /*!
   * Copy constructor taking a dsp::Password as parameter.
   * @param value
   */
  inline explicit Password(const Password &value) : Password() { value_ = value.value_ ;};

  /*!
   * Direct assignment operator. Allows assigning a std::string directly as a value.
   * @param value of type std::string which is being directly assigned.
   * @return
   */
  inline Password &operator=(const std::string &value) { value_ = value; return *this; }

  /*!
   * Direct assignment operator. Allows assigning a Password directly as a value.
   * @param value of type Password which is being directly assigned.
   * @return Password
   */
  inline Password &operator=(const Password &value) = default;

  /*!
   * Accessor returning the value as std::string.
   * @return std::string
   */
  inline std::string value() { return value_.get(); }

  /*!
   * Equality comparison operator.
   * @param rhs the other value that we compare against.
   * @return true if if both values are the same.
   */
  inline bool operator==(const Password &rhs) const {
    return static_cast<std::string>(value_) == static_cast<std::string>(rhs.value_);
  }

  /*!
   * Check for empty value.
   * @return
   */
  inline bool empty() {
    return static_cast<std::string>(value_).empty();
  }

 private:
  xsd::String value_;

};

}

#endif //SKUNKWORKS_ENTITIES_USER_PASSWORD_H_
