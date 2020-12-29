//
// Created by Lukas Rosenthaler on 29.12.20.
//

#include "shortname.h"

namespace dsp {

Shortname::Shortname() {
  shortname_.add_restriction(std::make_shared<xsd::RestrictionPattern>("([a-zA-Z_][\\w\\-]*)", "Short name restriction"));
  shortname_.add_restriction(std::make_shared<xsd::RestrictionMaxLength>(64, "Short name max length=64"));
}

Shortname::Shortname(const std::string &shortname) : Shortname() {
  shortname_ = shortname;
}

Shortname::Shortname(const xsd::String &shortname) : Shortname() {
  shortname_ = shortname;
}

Shortname::Shortname(const Shortname &shortname) : Shortname() {
  shortname_ = shortname.shortname_;
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

Shortname::operator std::string() const {
  return static_cast<std::string>(shortname_);
}

bool Shortname::operator==(const Shortname &other) const {
  return shortname_ == other.shortname_;
}

bool Shortname::operator==(const xsd::String &other) const {
  return shortname_ == other;
}

bool Shortname::operator==(const std::string &other) const {
  return static_cast<std::string>(shortname_) == other;
}

}