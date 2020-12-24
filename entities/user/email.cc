//
// Created by Ivan Subotic on 23/12/2020.
//

#include "email.h"

namespace entities::user {

Email::Email(const std::string &value) {
  value_ = "mailto:" + value;
}

}