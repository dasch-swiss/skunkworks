//
// Created by Lukas Rosenthaler on 21.12.20.
//

#include "configuration.h"

namespace dsp {

Configuration *Configuration::config_ptr = nullptr;

Configuration * Configuration::init() {
  if (config_ptr == nullptr) {
    config_ptr = new Configuration();
  }
  return config_ptr;
}

Configuration::Configuration() {
  data_model_prefix_ = "http://dsp.dasch.swiss/<project>/datamodel/";
  resclass_prefix_ = "http://dsp.dasch.swiss/<datamodel>/resclass/";
  property_prefix_ = "http://dsp.dasch.swiss/<datamodel>/property/";
  value_prefix_ = "http://dsp.dasch.swiss/system/value/";
}

std::string Configuration::resclass_prefix(const std::shared_ptr<DataModel> &in_data_model) const {
  std::string  pp = "<datamodel>";
  std::string tmpstr = resclass_prefix_;

  tmpstr.replace(tmpstr.find(pp), pp.length(), in_data_model->shortname());
  return tmpstr;
}

std::string Configuration::property_prefix(const std::shared_ptr<DataModel> &in_data_model) const {
  std::string  pp = "<datamodel>";
  std::string tmpstr = resclass_prefix_;

  tmpstr.replace(tmpstr.find(pp), pp.length(), in_data_model->shortname());
  return tmpstr;
}

std::string Configuration::value_prefix(const std::shared_ptr<Project> &project) const {
  return value_prefix_;
}


}
