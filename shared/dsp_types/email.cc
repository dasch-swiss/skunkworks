//
// Created by Ivan Subotic on 23/12/2020.
//

#include "email.h"

namespace dsp {

Email::Email() {
  value_.add_restriction(std::make_shared<xsd::RestrictionMinLength>(3, "The minimum Email length is 3."));
}

}