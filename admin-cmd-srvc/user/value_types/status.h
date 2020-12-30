//
// Created by Ivan Subotic on 28/12/2020.
//

#ifndef SKUNKWORKS_ADMIN_CMD_SRVC_USER_STATUS_H_
#define SKUNKWORKS_ADMIN_CMD_SRVC_USER_STATUS_H_

#include <string>
#include "shared/xsd_types/xsd.h"

namespace admin::user {

class Status {

 public:
  /*!
   * Default constructor creating a 'false' status.
   */
  Status();

  /*!
   * Constructor taking a std::string as parameter.
   * @param value
   */
  inline explicit Status(const bool &value) : Status() { value_ = value; };

  /*!
   * Constructor taking a xsd::String as parameter.
   * @param value
   */
  inline explicit Status(const xsd::Boolean &value) : Status() { value_ = value; };

  /*!
   * Copy constructor taking a dsp::FamilyName as parameter.
   * @param value
   */
  inline explicit Status(const Status &value) : Status() { value_ = value.value_ ;};

  /*!
   * Direct assignment operator. Allows assigning a std::string directly as a value.
   * @param value of type std::string which is being directly assigned.
   * @return
   */
  inline Status &operator=(const bool &value) { value_ = value; return *this; }

  /*!
   * Accessor returning the value as bool.
   * @return bool
   */
  inline bool value() { return static_cast<bool>(value_); }

  /*!
   * Equality comparison operator.
   * @param rhs the other value that we compare against.
   * @return true if if both values are the same.
   */
  inline bool operator==(const Status &rhs) const {
    return static_cast<bool>(value_) == static_cast<bool>(rhs.value_);
  }

 private:
  xsd::Boolean value_;

};

}

#endif //SKUNKWORKS_ADMIN_CMD_SRVC_USER_STATUS_H_
