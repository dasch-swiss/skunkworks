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
   * Default constructor not setting any value. Sets RestrictionPattern
   */
  Password();

  /*!
   * Constructor taking a xsd::string as parameter
   * @param value
   */
  inline explicit Password(const std::string &value) : Password() { value_ = value; }

 private:
  xsd::String value_;

};

}

#endif //SKUNKWORKS_ENTITIES_USER_PASSWORD_H_
