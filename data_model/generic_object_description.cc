//
// Created by Lukas Rosenthaler on 04.01.21.
//

#include "generic_object_description.h"

const char file_[] = __FILE__;

namespace dsp {

template<typename T>
void GenericObjectDescription::member(const std::string& name, const T& data) {
  data_[name] = std::make_shared<T>(data);
}

template<typename T>
T GenericObjectDescription::member(const std::string& name) const {
  try {
    T* ptr = dynamic_cast<T*>(data_.at(name).get());
    return *ptr;
  } catch (const std::out_of_range &err) {
    throw Error(file_, __LINE__, "GenericObjectDescription has no member \"" + name + "\".");
  }
}

bool GenericObjectDescription::has_member(const std::string& name) const {
  try {
    (void) data_.at(name);
    return true;
  } catch (const std::out_of_range &err) {
    return false;
  }
}

}