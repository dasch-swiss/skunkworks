//
// Created by Ivan Subotic on 23/12/2020.
//

#ifndef SKUNKWORKS_ENTITIES_USER_EMAIL_H_
#define SKUNKWORKS_ENTITIES_USER_EMAIL_H_

#include <string>
#include "../../../helpers/xsd_types/xsd.h"

namespace admin::user {

class Email {
 public:
  Email(const std::string &value);
  inline std::string value() { return static_cast<std::string>(value_); }

 private:
  xsd::AnyUri value_;
};

}

#endif //SKUNKWORKS_ENTITIES_USER_EMAIL_H_
