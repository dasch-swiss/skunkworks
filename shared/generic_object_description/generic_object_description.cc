//
// Created by Lukas Rosenthaler on 04.01.21.
//

#include "generic_object_description.h"

namespace dsp {

bool GenericObjectDescription::has_member(const std::string& name) const {
  try {
    (void) data_.at(name);
    return true;
  } catch (const std::out_of_range &err) {
    return false;
  }
}

}