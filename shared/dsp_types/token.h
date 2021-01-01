//
// Created by Ivan Subotic on 23/12/2020.
//

#ifndef SKUNKWORKS_ENTITIES_USER_TOKEN_H_
#define SKUNKWORKS_ENTITIES_USER_TOKEN_H_

#include <string>
#include "shared/xsd_types/xsd.h"

namespace dsp {

class Token {
 public:
  /*!
   * Default constructor. Sets Restrictions.
   */
  Token();

  /*!
   * Constructor taking a std::string as parameter.
   * @param value
   */
  inline explicit Token(const std::string &value) : Token() { value_ = value; };

  /*!
   * Constructor taking a xsd::String as parameter.
   * @param value
   */
  inline explicit Token(const xsd::String &value) : Token() { value_ = value; };

  /*!
   * Copy constructor taking a dsp::FamilyName as parameter.
   * @param value
   */
  inline explicit Token(const Token &value) : Token() { value_ = value.value_ ;};

  /*!
   * Direct assignment operator. Allows assigning a std::string directly as a value.
   * @param value of type std::string which is being directly assigned.
   * @return
   */
  inline Token &operator=(const std::string &value) { value_ = value; return *this; }

  /*!
   * Direct assignment operator. Allows assigning a Token directly as a value.
   * @param value of type Token which is being directly assigned.
   * @return Token
   */
  inline Token &operator=(const Token &value) = default;

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
  inline bool operator==(const Token &rhs) const {
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

#endif //SKUNKWORKS_ENTITIES_USER_TOKEN_H_
