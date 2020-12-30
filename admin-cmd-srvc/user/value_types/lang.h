//
// Created by Ivan Subotic on 23/12/2020.
//

#ifndef SKUNKWORKS_ENTITIES_USER_LANG_H_
#define SKUNKWORKS_ENTITIES_USER_LANG_H_

#include <string>
#include "shared/xsd_types/xsd.h"

namespace admin::user {

class Lang {

 public:
  Lang();
  Lang(const std::string &value);
  inline std::string value() { return value_.get(); }
  bool operator==(const Lang &rhs) const;
  bool operator!=(const Lang &rhs) const;

 private:
  xsd::String value_;

};

}

#endif //SKUNKWORKS_ENTITIES_USER_LANG_H_
