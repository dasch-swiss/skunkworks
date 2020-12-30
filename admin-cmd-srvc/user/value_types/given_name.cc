//
// Created by Ivan Subotic on 23/12/2020.
//
#include <string>
#include "shared/xsd_types/xsd.h"
#include "given_name.h"

namespace admin::user {

GivenName::GivenName(const std::string &value) {
  value_ = value;
}

bool GivenName::operator==(const GivenName &rhs) const {
  return static_cast<std::string>(value_) ==static_cast<std::string>(rhs.value_);
}

}