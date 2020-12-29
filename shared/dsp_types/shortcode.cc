//
// Created by Lukas Rosenthaler on 28.12.20.
//

#include "shortcode.h"

namespace dsp {

Shortcode::Shortcode() {
  shortcode_.add_restriction(std::make_shared<xsd::RestrictionPattern>("([a-fA-F0-9]{4})", "Short code restriction"));
}

Shortcode::Shortcode(const std::string &shortcode) : Shortcode() {
  shortcode_ = shortcode;
}

Shortcode::Shortcode(const xsd::String &shortcode) : Shortcode() {
  shortcode_ = shortcode;
}

Shortcode::Shortcode(const Shortcode &shortcode) : Shortcode() {
  shortcode_ = shortcode.shortcode_;
}

Shortcode &Shortcode::operator=(const Shortcode &shortcode) {
  shortcode_ = shortcode.shortcode_;
  return *this;
}

Shortcode &Shortcode::operator=(const xsd::String &shortcode) {
  shortcode_ = shortcode;
  return *this;
}

Shortcode &Shortcode::operator=(const std::string &shortcode) {
  shortcode_ = shortcode;
  return *this;
}

Shortcode::operator std::string() const {
  return static_cast<std::string>(shortcode_);
}

bool Shortcode::operator==(const Shortcode &other) const {
  return shortcode_ == other.shortcode_;
}

bool Shortcode::operator==(const xsd::String &other) const {
  return shortcode_ == other;
}

bool Shortcode::operator==(const std::string &other) const {
  return static_cast<std::string>(shortcode_) == other;
}


}