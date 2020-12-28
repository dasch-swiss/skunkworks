//
// Created by Ivan Subotic on 23/12/2020.
//

#ifndef SKUNKWORKS_ENTITIES_USER_FAMILY_NAME_H_
#define SKUNKWORKS_ENTITIES_USER_FAMILY_NAME_H_

#include <string>
#include "helpers/xsd_types/xsd.h"

namespace admin::user {

class FamilyName {
 public:
  FamilyName(const std::string &value);
  inline std::string value() { return value_.get(); }
  bool operator==(const FamilyName &rhs) const;

 private:
  xsd::String value_;

};

}

#endif //SKUNKWORKS_ENTITIES_USER_FAMILY_NAME_H_
