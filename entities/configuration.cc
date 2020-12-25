//
// Created by Lukas Rosenthaler on 21.12.20.
//

#include "configuration.h"

namespace dsp {

Configuration *Configuration::config_ptr = nullptr;

const Configuration *Configuration::init() {
  if (config_ptr == nullptr) {
    config_ptr = new Configuration();
  }
  return config_ptr;
}

Configuration::Configuration() {
  resclass_prefix_ = "http://dsp.dasch.swiss/resclass/";
  property_prefix_ = "http://dsp.dasch.swiss/property/";
}

}