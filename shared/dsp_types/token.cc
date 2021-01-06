//
// Created by Ivan Subotic on 23/12/2020.
//

#include "shared/xsd_types/xsd.h"
#include "token.h"

namespace dsp {

Token::Token() {
  value_.add_restriction(std::make_shared<xsd::RestrictionMinLength>(10, "The minimum token length is 10."));
}

}