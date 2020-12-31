//
// Created by Ivan Subotic on 23/12/2020.
//

#ifndef SKUNKWORKS_ENTITIES_USER_EMAIL_H_
#define SKUNKWORKS_ENTITIES_USER_EMAIL_H_

#include <string>
#include "shared/xsd_types/xsd.h"

namespace admin::user {

class Email {
 public:
  /*!
   * Default constructor. Sets Restrictions.
   */
  Email();

  /*!
   * Constructor taking a std::string as parameter.
   * @param value
   */
  inline explicit Email(const std::string &value) : Email() { value_ = "mailto:" + value; };

  /*!
   * Constructor taking a xsd::String as parameter.
   * @param value
   */
  inline explicit Email(const xsd::String &value) : Email() { value_ = "mailto:" + static_cast<std::string>(value); };

  /*!
   * Copy constructor taking a dsp::Email as parameter.
   * @param value
   */
  inline explicit Email(const Email &value) : Email() { value_ = "mailto:" + static_cast<std::string>(value.value_); };

  /*!
   * Direct assignment operator. Allows assigning a std::string directly as a value.
   * @param value of type std::string which is being directly assigned.
   * @return
   */
  inline Email &operator=(const std::string &value) { value_ = "mailto:" + value; return *this; }

  /*!
   * Direct assignment operator. Allows assigning a Email directly as a value.
   * @param value of type Email which is being directly assigned.
   * @return Email
   */
  inline Email &operator=(const Email &value) = default;

  /*!
   * Accessor returning the value as std::string.
   * @return std::string
   */
  inline std::string value() { return static_cast<std::string>(value_).substr(7); }

  /*!
   * Equality comparison operator.
   * @param rhs the other value that we compare against.
   * @return true if if both values are the same.
   */
  inline bool operator==(const Email &rhs) const {
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
  xsd::AnyUri value_;
};

}

#endif //SKUNKWORKS_ENTITIES_USER_EMAIL_H_
