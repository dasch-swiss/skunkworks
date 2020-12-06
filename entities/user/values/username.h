//
// Created by Ivan Subotic on 29/11/2020.
//

#ifndef SKUNKWORKS_ENTITIES_ADMIN_USER_VALUES_USERNAME_H_
#define SKUNKWORKS_ENTITIES_ADMIN_USER_VALUES_USERNAME_H_

#include <string>

static const char __file__[] = __FILE__;

namespace entities::user {

class Username {
 public:
  Username(const std::string& value);
  inline std::string value() {return value_; }

 private:
  std::string value_;
};

} // namespace entities::user



#endif //SKUNKWORKS_ENTITIES_ADMIN_USER_VALUES_USERNAME_H_
