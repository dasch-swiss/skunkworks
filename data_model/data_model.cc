//
// Created by Lukas Rosenthaler on 21.12.20.
//

#include <sstream>

#include "shared/error/error.h"
#include "shared/dsp_types/identifier.h"
#include "shared/dsp_types/shortname.h"

#include "data_model.h"
#include "domain_model.h"
#include "project.h"
#include "resource_class.h"

static const char file_[] = __FILE__;

namespace dsp {

DataModel::DataModel() {
  id_ = dsp::Identifier();
  creation_date_ = xsd::DateTimeStamp(); // current timestamp
}


DataModel::DataModel(const std::shared_ptr<Agent> &created_by, const dsp::Shortname &shortname) : DataModel() {
  created_by_ = created_by;
  shortname_ = shortname;
}


DataModel::DataModel(const std::shared_ptr<Agent> &created_by, const xsd::String& shortname) : DataModel() {
  created_by_ = created_by;
  shortname_ = shortname;
}

DataModel::DataModel(const std::shared_ptr<Agent> &created_by, const std::string& shortname) : DataModel() {
  created_by_ = created_by;
  shortname_ = shortname;
}

DataModel::DataModel(const nlohmann::json& json_obj, std::shared_ptr<DomainModel>& model) {
  if (json_obj.contains("version") && (json_obj["version"] == 1) && json_obj.contains("type") && (json_obj["type"] == "DataModel")) {
    if (json_obj.contains("id")) {
      id_ = dsp::Identifier(json_obj["id"]);
      if (!json_obj.contains("creation_date")) throw Error(file_, __LINE__, R"("DataModel" has no "creation_date")");
      creation_date_ = xsd::DateTimeStamp(json_obj["creation_date"]);

      if (!json_obj.contains("created_by")) throw Error(file_, __LINE__, R"("DataModel" has no "created_by")");
      dsp::Identifier created_by_id(json_obj["created_by"]);
      std::shared_ptr<Agent> created_by = model->agent(created_by_id);
      created_by_ = created_by;

      if (!json_obj.contains("shortname")) throw Error(file_, __LINE__, R"("DataModel" has no "shortname")");
      shortname_ = json_obj["shortname"];

      if (!json_obj.contains("project")) throw Error(file_, __LINE__, R"("DataModel" has no "project")");
      dsp::Identifier project_id(json_obj["project"]);
      std::shared_ptr<Project> project = model->project(project_id);
      project_ = project;

      std::vector<std::string> data_model_ids = json_obj["resource_classes"];
      std::vector<std::string> property_ids = json_obj["properties"];

      if (json_obj.contains("last_modification_date") && json_obj.contains("modified_by")) {
        last_modification_date_ = xsd::DateTimeStamp(json_obj["last_modification_date"]);
        dsp::Identifier modified_by_id(json_obj["modified_by"]);
        std::shared_ptr<Agent> modified_by = model->agent(modified_by_id);
        modified_by_ = modified_by;
      }
    } else{
      throw Error(file_, __LINE__, R"("DataModel" serialization has no "id".)");
    }
  } else{
    throw Error(file_, __LINE__, R"("DataModel" serialization not consistent.)");
  }
}

void DataModel::add_resource_class(const std::shared_ptr<ResourceClass> &resource_class) {
  if (resource_class->in_data_model() != nullptr) {
    throw Error(file_, __LINE__, "Resource class is already in data model: " + static_cast<std::string>(resource_class->in_data_model()->shortname()));
  }
  try {
    ResourceClassPtr tmp = resource_classes_.at(resource_class->id());
    std::ostringstream ss;
    ss << "Resource class \"" << resource_class->class_label().get("en") << "\" (" << resource_class->id() <<
    ") already exists in data model \"" << id_ << "\"!";
    throw (Error(file_, __LINE__, ss.str()));
  }
  catch (const std::out_of_range &err) {
    resource_classes_[resource_class->id()] = resource_class;
    resource_class->in_data_model_ = shared_from_this();
    return;
  } // TODO: Use C++20 with contains ASAP!
}

std::optional<ResourceClassPtr> DataModel::get_resource_class(const dsp::Identifier &resource_class_id) const {
  auto res = resource_classes_.find(resource_class_id);
  if (res == resource_classes_.end()) {
    return {};
  } else {
    return res->second;
  }
}

std::optional<ResourceClassPtr> DataModel::remove_resource_class(const dsp::Identifier &resource_class_id) {
  //
  // ToDo: Check here if data model is in use!!!
  //
  auto res = resource_classes_.find(resource_class_id);
  if (res == resource_classes_.end()) {
    return {};
  } else {
    resource_classes_.erase(resource_class_id);
    ResourceClassPtr resource_class_ptr = res->second;
    resource_class_ptr->in_data_model_ = std::weak_ptr<DataModel>();
    return resource_class_ptr;
  }
}

void DataModel::add_property(const std::shared_ptr<Property> &property) {
  if (property->in_data_model() != nullptr) {
    throw Error(file_, __LINE__, "Property is already in data model: " + static_cast<std::string>(property->in_data_model()->shortname()));
  }
  try {
    ResourceClassPtr tmp = resource_classes_.at(property->id());
    std::ostringstream ss;
    ss << "Resource class \"" << property->class_label().get("en") << "\" (" << property->id() <<
       ") already exists in data model \"" << id_ << "\"!";
    throw (Error(file_, __LINE__, ss.str()));
  }
  catch (const std::out_of_range &err) {
    properties_[property->id()] = property;
    property->in_data_model_ = shared_from_this();
    return;
  } // TODO: Use C++20 with contains ASAP!
}

std::optional<PropertyPtr> DataModel::get_property(const dsp::Identifier &property_id) const {
  auto res = properties_.find(property_id);
  if (res == properties_.end()) {
    return {};
  } else {
    return res->second;
  }
}

std::optional<PropertyPtr> DataModel::remove_property(const dsp::Identifier &property_id) {
  //
  // ToDo! Check here if property is in use in any data model!!!
  //
  for (const auto &resclass: resource_classes_) {
    for(const auto &prop: resclass.second->has_properties_) {
      if (prop.first == property_id) {
        std::ostringstream ss;
        ss << "Resource class " << resclass.second->class_label().get("en") << " is using the property!";
        throw dsp::Error(file_, __LINE__, ss.str());
      }
    }
  }
  auto res = properties_.find(property_id);
  if (res == properties_.end()) {
    return {};
  } else {
    properties_.erase(property_id);
    PropertyPtr property_ptr = res->second;
    property_ptr->in_data_model_ = std::weak_ptr<DataModel>();
    return property_ptr;
  }
}

nlohmann::json DataModel::to_json() {
  std::vector<std::string> resource_class_ids;
  for (auto [key, value]: resource_classes_) {
    resource_class_ids.push_back(key);
  }

  std::vector<std::string> property_ids;
  for (auto [key, value]: properties_) {
    property_ids.push_back(key);
  }

  nlohmann::json json_obj = {
      {"version", 1},
      {"type", "DataModel"},
      {"id", id_},
      {"shortname", shortname_},
      {"creation_date", creation_date_},
      {"created_by", created_by_.lock()->id()},
      {"project", project_.lock()->id()},
      {"resource_classes", resource_class_ids},
      {"properties", property_ids},
  };
  if (!modified_by_.expired()) {
    json_obj["last_modification_date"] = last_modification_date_;
    json_obj["modified_by"] = modified_by_.lock()->id();
  }
  return json_obj;
}

}