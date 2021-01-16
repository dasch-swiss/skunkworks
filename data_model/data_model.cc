//
// Created by Lukas Rosenthaler on 21.12.20.
//

#include <sstream>

#include "shared/error/error.h"
#include "shared/dsp_types/identifier.h"
#include "shared/dsp_types/shortname.h"

#include "project.h"
#include "resource_class.h"
#include "data_model.h"

static const char file_[] = __FILE__;

namespace dsp {

DataModel::DataModel(const dsp::Identifier &created_by, const dsp::Shortname &shortname) {
  id_ = Identifier("DataModel", shortname.to_string());
  shortname_ = shortname;
  creation_date_ = xsd::DateTimeStamp(); // current timestamp
  created_by_ = created_by;
  project_ = dsp::Identifier::empty_identifier();
}

std::shared_ptr<DataModel> DataModel::Factory(
    const dsp::Identifier &created_by,
    const dsp::Shortname& shortname,
    std::shared_ptr<Observer> obs) {
  std::shared_ptr<DataModel> tmp(new DataModel(created_by, shortname));
  if (obs) tmp->attach(obs);
  tmp->add_item<DataModel>();
  tmp->notify(ObserverAction::CREATE, tmp);
  return tmp;
}

DataModel::DataModel(const nlohmann::json& json_obj) {
  if (json_obj.contains("version") && (json_obj["version"] == 1) && json_obj.contains("type") && (json_obj["type"] == "DataModel")) {
    if (json_obj.contains("id")) {
      id_ = dsp::Identifier(json_obj["id"].get<std::string>());
      if (!json_obj.contains("creation_date")) throw Error(file_, __LINE__, R"("DataModel" has no "creation_date")");
      creation_date_ = xsd::DateTimeStamp(json_obj["creation_date"].get<std::string>());

      if (!json_obj.contains("created_by")) throw Error(file_, __LINE__, R"("DataModel" has no "created_by")");
      created_by_ = dsp::Identifier(json_obj["created_by"].get<std::string>());

      if (!json_obj.contains("shortname")) throw Error(file_, __LINE__, R"("DataModel" has no "shortname")");
      shortname_ = json_obj["shortname"].get<std::string>();

      if (!json_obj.contains("project")) throw Error(file_, __LINE__, R"("DataModel" has no "project")");
      project_ = dsp::Identifier(json_obj["project"].get<std::string>());

      std::vector<std::string> resource_class_ids = json_obj["resource_classes"];
      resource_classes_ = std::unordered_set<dsp::Identifier>(resource_class_ids.begin(), resource_class_ids.end());

      std::vector<std::string> property_ids = json_obj["properties"];
      properties_ = std::unordered_set<dsp::Identifier>(property_ids.begin(), property_ids.end());

      if (json_obj.contains("last_modification_date") && json_obj.contains("modified_by")) {
        last_modification_date_ = xsd::DateTimeStamp(json_obj["last_modification_date"]);
        modified_by_ = dsp::Identifier(json_obj["modified_by"]);
      }
    } else{
      throw Error(file_, __LINE__, R"("DataModel" serialization has no "id".)");
    }
  } else{
    throw Error(file_, __LINE__, R"("DataModel" serialization not consistent.)");
  }
}

std::shared_ptr<DataModel> DataModel::Factory(const nlohmann::json& json_obj, std::shared_ptr<Observer> obs) {
  std::shared_ptr<DataModel> tmp(new DataModel(json_obj));
  if (ModelItem::item_exists(tmp->id())) { //
    throw Error(file_, __LINE__, R"("DataModel" with same "id" already exists!)");
  }
  if (obs) tmp->attach(obs);
  tmp->add_item<DataModel>();
  tmp->notify(ObserverAction::CREATE, tmp);
  return tmp;
}

std::shared_ptr<Project> DataModel::project() const {
  return get_item<Project>(project_);
}


void DataModel::add_resource_class(const Identifier &resource_class_id, const Identifier& agent_id) {
  if (resource_classes_.find(resource_class_id) != resource_classes_.end()) {
    throw Error(file_,
                __LINE__,
                R"(Data model already assigned to project "")" + static_cast<std::string>(shortname_) + R"(".)");
  }
  resource_classes_.insert(resource_class_id);
  last_modification_date_ = xsd::DateTimeStamp();
  modified_by_ = agent_id;
  std::shared_ptr<ResourceClass> tmp = get_item<ResourceClass>(resource_class_id);
  tmp->in_data_model_ = id_;
  tmp->modified_by_ = agent_id;
  tmp->last_modification_date_ = last_modification_date_;
  tmp->notify(ObserverAction::UPDATE, tmp); // DataModel's project_ changed...
  notify(ObserverAction::UPDATE, shared_from_this());
}

std::optional<ResourceClassPtr> DataModel::get_resource_class(const dsp::Identifier &resource_class_id) const {
  auto res = resource_classes_.find(resource_class_id);
  if (res == resource_classes_.end()) {
    return {};
  } else {
    return get_item<ResourceClass>(*res);
  }
}

std::optional<ResourceClassPtr> DataModel::remove_resource_class(const dsp::Identifier &resource_class_id, const Identifier& agent_id) {
  //
  // ToDo: Check here if resource class is in use!!!
  //
  auto res = resource_classes_.find(resource_class_id);
  if (res == resource_classes_.end()) {
    return {};
  } else {
    ResourceClassPtr resource_class_ptr = get_item<ResourceClass>(resource_class_id);
    resource_classes_.erase(resource_class_id);
    last_modification_date_ = xsd::DateTimeStamp();
    modified_by_ = agent_id;
    resource_class_ptr->in_data_model_ = Identifier::empty_identifier();
    resource_class_ptr->last_modification_date_ = last_modification_date_;
    resource_class_ptr->modified_by_ = agent_id;
    resource_class_ptr->notify(ObserverAction::UPDATE, resource_class_ptr); // Property's in_data_model_ changed...
    notify(ObserverAction::UPDATE, shared_from_this());
    return resource_class_ptr;
  }
}

void DataModel::add_property(const dsp::Identifier& property_id, const dsp::Identifier &agent_id) {
  if (properties_.find(property_id) != properties_.end()) {
    throw Error(file_,
                __LINE__,
                R"(Property already assigned to data model "")" + static_cast<std::string>(shortname_) + R"(".)");
  }
  properties_.insert(property_id);
  last_modification_date_ = xsd::DateTimeStamp();
  modified_by_ = agent_id;
  std::shared_ptr<Property> tmp = get_item<Property>(property_id);
  tmp->in_data_model_ = id_;
  tmp->last_modification_date_ = last_modification_date_;
  tmp->modified_by_ = modified_by_;
  tmp->notify(ObserverAction::UPDATE, tmp); // Property's in_data_model_ changed...
  notify(ObserverAction::UPDATE, shared_from_this());
}

std::optional<PropertyPtr> DataModel::get_property(const dsp::Identifier &property_id) const {
  auto res = properties_.find(property_id);
  if (res == properties_.end()) {
    return {};
  } else {
    return get_item<Property>(*res);
  }
}

std::optional<PropertyPtr> DataModel::remove_property(const dsp::Identifier &property_id, const dsp::Identifier& agent_id) {
  //
  // ToDo: Check here if data model is in use!!!
  //
  auto res = properties_.find(property_id);
  if (res == properties_.end()) {
    return {};
  } else {
    PropertyPtr property = get_item<Property>(property_id);
    //
    // Check if property is referenced as super-property
    //
    for (const auto& prop_id: properties_) {
      PropertyPtr p = dsp::ModelItem::get_item<Property>(prop_id);
      if (p->sub_property_of_id() == property_id) {
        throw Error(file_, __LINE__, R"("remove_property" failed: Property is referenced as superproperty.)");
      }
    }
    //
    // Check if property is referenced by and ResourceClass
    //
    for (const auto& res_id: resource_classes_) {
      ResourceClassPtr resclass = dsp::ModelItem::get_item<ResourceClass>(res_id);
      if (resclass->has_properties_.find(property_id) != resclass->has_properties_.end()) {
        throw Error(file_, __LINE__, R"("remove_property" failed: Property is referenced in ResourceClass.)");
      }
    }
    properties_.erase(property_id);
    last_modification_date_ = xsd::DateTimeStamp();
    modified_by_ = agent_id;
    property->in_data_model_ = Identifier::empty_identifier();
    property->last_modification_date_ = last_modification_date_;
    property->modified_by_ = modified_by_;
    property->notify(ObserverAction::UPDATE, property); // property's in_data_model_ changed...
    notify(ObserverAction::UPDATE, shared_from_this());
    return property;
  }
}

nlohmann::json DataModel::to_json() {
  std::vector<std::string> resource_class_ids(resource_classes_.begin(), resource_classes_.end());

  std::vector<std::string> property_ids(properties_.begin(), properties_.end());

  nlohmann::json json_obj = {
      {"version", 1},
      {"type", "DataModel"},
      {"id", id_},
      {"shortname", shortname_},
      {"creation_date", creation_date_},
      {"created_by", created_by_},
      {"project", project_},
      {"resource_classes", resource_class_ids},
      {"properties", property_ids},
  };

  if (modified_by_ != dsp::Identifier::empty_identifier()) {
    json_obj["last_modification_date"] = last_modification_date_;
    json_obj["modified_by"] = modified_by_;
  }
  return json_obj;
}

}