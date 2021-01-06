//
// Created by Lukas Rosenthaler on 29.12.20.
//

#include "shortname.h"

namespace dsp {

Shortname::Shortname() {
  shortname_.add_restriction(std::make_shared<xsd::RestrictionPattern>("([a-zA-Z_][\\w\\-]*)", "Short name restriction"));
  shortname_.add_restriction(std::make_shared<xsd::RestrictionMaxLength>(64, "Short name max length=64"));
}


Shortname &Shortname::operator=(const Shortname &shortname) {
  shortname_ = shortname.shortname_;
  return *this;
}

Shortname &Shortname::operator=(const xsd::String &shortname) {
  shortname_ = shortname;
  return *this;
}

Shortname &Shortname::operator=(const std::string &shortname) {
  shortname_ = shortname;
  return *this;
}

}