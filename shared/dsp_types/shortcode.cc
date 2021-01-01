//
// Created by Lukas Rosenthaler on 28.12.20.
//

#include "shortcode.h"

using namespace std::string_literals;

namespace dsp {

Shortcode::Shortcode() {
  shortcode_.add_restriction(std::make_shared<xsd::RestrictionPattern>("([a-fA-F0-9]{4})"s, "Short code restriction"s));
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


}