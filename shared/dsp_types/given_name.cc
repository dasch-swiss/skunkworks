//
// Created by Ivan Subotic on 23/12/2020.
//
#include <string>
#include "shared/xsd_types/xsd.h"
#include "given_name.h"

namespace dsp {

GivenName::GivenName() {
  value_.add_restriction(std::make_shared<xsd::RestrictionMinLength>(2, "The minimum GivenName length is 2."));
}

}