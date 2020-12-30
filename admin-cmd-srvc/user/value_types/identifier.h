//
// Created by Ivan Subotic on 23/12/2020.
//

#ifndef SKUNKWORKS_ENTITIES_USER_IDENTIFIER_H_
#define SKUNKWORKS_ENTITIES_USER_IDENTIFIER_H_

#include <string>
#include "shared/xsd_types/xsd.h"

namespace admin::user {

class Identifier {
 public:
  /*!
   * Default constructor generating a random UUID. Sets Restrictions.
   */
  Identifier();

  /*!
   * Constructor taking a std::string as parameter.
   * @param value
   */
  inline explicit Identifier(const std::string &value) : Identifier() { value_ = value; };

  /*!
   * Constructor taking a xsd::String as parameter.
   * @param value
   */
  inline explicit Identifier(const xsd::String &value) : Identifier() { value_ = value; };

  /*!
   * Copy constructor taking a dsp::Identifier as parameter.
   * @param value
   */
  inline explicit Identifier(const Identifier &value) : Identifier() { value_ = value.value_ ;};

  /*!
   * Direct assignment operator. Allows assigning a std::string directly as a value.
   * @param value of type std::string which is being directly assigned.
   * @return
   */
  inline Identifier &operator=(const std::string &value) { value_ = value; return *this; }

  /*!
   * Accessor returning the value as std::string.
   * @return std::string
   */
  inline std::string value() {return value_.get(); }



  /*!
   * Equality comparison operator.
   * @param rhs the other value that we compare against.
   * @return true if if both values are the same.
   */
  inline bool operator==(const Identifier &rhs) const {
    return static_cast<std::string>(value_) == static_cast<std::string>(rhs.value_);
  }

 private:
  xsd::String value_;

};

}

#endif //SKUNKWORKS_ENTITIES_USER_IDENTIFIER_H_
