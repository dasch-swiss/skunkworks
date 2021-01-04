//
// Created by Ivan Subotic on 23/12/2020.
//

#ifndef SKUNKWORKS_ENTITIES_USER_IDENTIFIER_H_
#define SKUNKWORKS_ENTITIES_USER_IDENTIFIER_H_

#include <string>
#include "shared/uuid.h"
#include "shared/xsd_types/xsd.h"

namespace dsp {

class Identifier {
 public:
  /*!
   * Default constructor generating a random UUID. Sets Restrictions.
   */
  inline Identifier() = default;

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
  inline Identifier(const Identifier &value) : Identifier() { value_ = value.value_; };

  /*!
   * Direct assignment operator. Allows assigning a std::string directly as a value.
   * @param value of type std::string which is being directly assigned.
   * @return
   */
  inline Identifier &operator=(const std::string &value) { value_ = value; return *this; };

  /*!
   * Set the Identifier to a random v4 UUID.
   */
  inline Identifier with_uuid_v4() {value_ = uuid::generate_uuid_v4(); return *this; };

  /*!
   * Accessor returning the value as std::string.
   * @return std::string
   */
  inline std::string value() { return value_.get(); };

  /*!
   * Check for null.
   */
  inline bool is_null() { return value_.empty(); };

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
