//
// Created by Ivan Subotic on 29/11/2020.
//

#ifndef SKUNKWORKS_ENTITIES_ADMIN_USER_VALUES_USERNAME_H_
#define SKUNKWORKS_ENTITIES_ADMIN_USER_VALUES_USERNAME_H_

#include <string>
#include "shared/xsd_types/xsd.h"

namespace admin::user {

class Username {
 public:
  /*!
   * Default constructor. Sets Restrictions.
   */
  Username();

  /*!
   * Constructor taking a std::string as parameter.
   * @param value
   */
  inline explicit Username(const std::string &value) : Username() { value_ = value; };

  /*!
   * Constructor taking a xsd::String as parameter.
   * @param value
   */
  inline explicit Username(const xsd::String &value) : Username() { value_ = value; };

  /*!
   * Copy constructor taking a dsp::FamilyName as parameter.
   * @param value
   */
  inline explicit Username(const Username &value) : Username() { value_ = value.value_ ;};

  /*!
   * Direct assignment operator. Allows assigning a std::string directly as a value.
   * @param value of type std::string which is being directly assigned.
   * @return
   */
  inline Username &operator=(const std::string &value) { value_ = value; return *this; };

  /*!
   * Direct assignment operator. Allows assigning a Username directly as a value.
   * @param value of type Username which is being directly assigned.
   * @return Username
   */
  inline Username &operator=(const Username &value) = default;

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
  inline bool operator==(const Username &rhs) const {
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

} // namespace entities::user



#endif //SKUNKWORKS_ENTITIES_ADMIN_USER_VALUES_USERNAME_H_
