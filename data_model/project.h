//
// Created by Lukas Rosenthaler on 21.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_PROJECT_H_
#define SKUNKWORKS_ENTITIES_PROJECT_H_

#include <string>
#include <unordered_map>

#include "helpers/xsd_types/xsd_any_uri.h"
#include "helpers/xsd_types/xsd_restriction.h"

#include "data_model.h"

namespace dsp {


class Project {
 public:
  Project();

  inline Project(const xsd::String &shortcode) : Project() {
    shortcode_ = shortcode;
  }

  inline Project(const std::string &shortcode) : Project(xsd::String(shortcode)) { }

  void add_data_model(const std::shared_ptr<DataModel> &data_model);

  std::shared_ptr<DataModel> get_data_model(const xsd::AnyUri &data_model_id);

  void remove_data_model(const xsd::AnyUri &data_model_id);

  inline xsd::AnyUri id() const { return id_; }

  inline xsd::String shortcode() const { return shortcode_; }

 private:
  xsd::AnyUri id_;
  xsd::String shortcode_;
  std::unordered_map<xsd::AnyUri, std::shared_ptr<DataModel>> data_models_;
};

using ProjectPtr = std::shared_ptr<Project>;

}


#endif //SKUNKWORKS_ENTITIES_PROJECT_H_
