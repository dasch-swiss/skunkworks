//
// Created by Ivan Subotic on 23/12/2020.
//

#include "helpers/xsd_types/xsd.h"
#include "family_name.h"


namespace admin::user {

FamilyName::FamilyName(const std::string &value) {
  value_ = value;
}

bool FamilyName::operator==(const FamilyName &rhs) const {
  return static_cast<std::string>(value_) == static_cast<std::string>(rhs.value_);
}

}