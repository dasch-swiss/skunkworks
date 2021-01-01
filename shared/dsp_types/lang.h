//
// Created by Ivan Subotic on 23/12/2020.
//

#ifndef SKUNKWORKS_ENTITIES_USER_LANG_H_
#define SKUNKWORKS_ENTITIES_USER_LANG_H_

#include <string>
#include "shared/xsd_types/xsd.h"

namespace dsp {

class Lang {
 public:
  /*!
   * Default constructor. Sets Restrictions.
   */
  Lang();

  /*!
   * Constructor taking a std::string as parameter.
   * @param value
   */
  inline explicit Lang(const std::string &value) : Lang() { value_ = value; };

  /*!
   * Constructor taking a xsd::String as parameter.
   * @param value
   */
  inline explicit Lang(const xsd::String &value) : Lang() { value_ = value; };

  /*!
   * Copy constructor taking a dsp::FamilyName as parameter.
   * @param value
   */
  inline explicit Lang(const Lang &value) : Lang() { value_ = value.value_ ;};

  /*!
   * Direct assignment operator. Allows assigning a std::string directly as a value.
   * @param value of type std::string which is being directly assigned.
   * @return Lang
   */
  inline Lang &operator=(const std::string &value) { value_ = value; return *this; };

  /*!
   * Direct assignment operator. Allows assigning a Lang directly as a value.
   * @param value of type FamilyName which is being directly assigned.
   * @return Lang
   */
  inline Lang &operator=(const Lang &value) = default;

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
  inline bool operator==(const Lang &rhs) const {
    return static_cast<std::string>(value_) == static_cast<std::string>(rhs.value_);
  }

  /*!
   * Inequality comparison operator.
   * @param rhs the other value that we compare against.
   * @return true if values are not the same.
   */
  inline bool operator!=(const Lang &rhs) const {
    return static_cast<std::string>(value_) != static_cast<std::string>(rhs.value_);
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

#endif //SKUNKWORKS_ENTITIES_USER_LANG_H_
