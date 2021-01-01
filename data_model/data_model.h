//
// Created by Lukas Rosenthaler on 21.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_DATA_MODEL_H_
#define SKUNKWORKS_ENTITIES_DATA_MODEL_H_

#include <string>
#include <unordered_map>

#include "shared/xsd_types/xsd.h"


namespace dsp {

class Project;
class ResourceClass;
class Property;

class DataModel {
 public:
  DataModel() = default;

  DataModel(const std::string &shortname);

  inline xsd::AnyUri id() { return id_; }
  inline std::string shortname() { return shortname_; }
  inline xsd::AnyUri project_id() { return project_id_; }

  void add_resource_class(const std::shared_ptr<ResourceClass> &resource_class);
  friend Project; // gets access to call project_id(...) to set the project id
 private:

  xsd::AnyUri id_;
  std::string shortname_;
  xsd::AnyUri project_id_;
  std::unordered_map<xsd::AnyUri, std::shared_ptr<ResourceClass>> resource_classes_;
  std::unordered_map<std::string, std::shared_ptr<Property>> properties_;

  inline void project_id(const xsd::AnyUri &project_id) { project_id_ = project_id; }

};

using DataModelPtr = std::shared_ptr<DataModel>;

}


#endif //SKUNKWORKS_ENTITIES_DATA_MODEL_H_
