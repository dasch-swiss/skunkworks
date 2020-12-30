//
// Created by Ivan Subotic on 23/12/2020.
//

#include "shared/xsd_types/xsd.h"

#include "password.h"

namespace admin::user {

Password::Password(){
  value_.add_restriction(std::make_shared<xsd::RestrictionMinLength>(4, "The minimum password length is 4"));
}

}