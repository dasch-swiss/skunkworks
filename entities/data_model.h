//
// Created by Lukas Rosenthaler on 21.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_DATA_MODEL_H_
#define SKUNKWORKS_ENTITIES_DATA_MODEL_H_

#include <string>
#include <unordered_map>

#include "helpers/xsd_types/xsd.h"

#include "resource_class.h"
#include "project.h"

namespace dsp {

class DataModel {
 public:
  DataModel() = default;

 private:
  xsd::AnyUri id_;
  std::shared_ptr<Project> project_;
  std::unordered_map<xsd::AnyUri, std::shared_ptr<ResourceClass>> resources_;
  std::unordered_map<std::string, std::shared_ptr<Property>> properties_;
};

}


#endif //SKUNKWORKS_ENTITIES_DATA_MODEL_H_
