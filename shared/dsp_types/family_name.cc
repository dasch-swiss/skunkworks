//
// Created by Ivan Subotic on 23/12/2020.
//

#include "shared/xsd_types/xsd.h"
#include "family_name.h"

namespace dsp {

FamilyName::FamilyName() {
  value_.add_restriction(std::make_shared<xsd::RestrictionMinLength>(2, "The minimum family name length is 2."));
}

}
