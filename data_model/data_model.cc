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
#include "all_properties.h"

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
      if (!json_obj.contains("creation_date")) throw Error(file_, __LINE__,
          fmt::format(R"(DataModel with id="{}" has no "creation_date")"s, id_.to_string()));
      creation_date_ = xsd::DateTimeStamp(json_obj["creation_date"].get<std::string>());

      if (!json_obj.contains("created_by")) throw Error(file_, __LINE__,
          fmt::format(R"(DataModel with id="{}" has no "created_by")"s, id_.to_string()));
      created_by_ = dsp::Identifier(json_obj["created_by"].get<std::string>());

      if (!json_obj.contains("shortname")) throw Error(file_, __LINE__,
          fmt::format(R"(DataModel with id="{}" has no "shortname")"s, id_.to_string()));
      shortname_ = json_obj["shortname"].get<std::string>();

      if (!json_obj.contains("project")) throw Error(file_, __LINE__,
          fmt::format(R"(DataModel with id="{}" has no "project")"s, id_.to_string()));
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
      throw Error(file_, __LINE__, R"(DataModel serialization has no "id".)"s);
    }
  } else{
    throw Error(file_, __LINE__, R"(DataModel serialization is not consistent.)"s);
  }
}

std::shared_ptr<DataModel> DataModel::Factory(const nlohmann::json& json_obj, std::shared_ptr<Observer> obs) {
  std::shared_ptr<DataModel> tmp(new DataModel(json_obj));
  if (ModelItem::item_exists(tmp->id())) { //
    throw Error(file_, __LINE__,
        fmt::format(R"(DataModel with same id="{}" already exists!)"s, tmp->id().to_string()));
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
    throw Error(file_, __LINE__,
        fmt::format(R"(ResourceClass width id="{}" already assigned to data model "{}" ({}))"s,
            resource_class_id.to_string(), shortname_.to_string(), id_.to_string()));
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

void DataModel::remove_resource_class(const dsp::Identifier &resource_class_id, const Identifier& agent_id) {
  //
  // ToDo: Check here if resource class is in use!!!
  //
  auto res = resource_classes_.find(resource_class_id);
  if (res == resource_classes_.end()) {
    throw Error(file_, __LINE__, fmt::format(R"(Resource class with id="{}" is not in data model "{}"!)",
        resource_class_id.to_string(), shortname_.to_string()));
  }
  //
  // Check if resource class is super class of another resource class
  //
  ResourceClassPtr resource_class_ptr = get_item<ResourceClass>(resource_class_id);
  for (const auto& rc_id: resource_classes_) {
    ResourceClassPtr r = ModelItem::get_item<ResourceClass>(rc_id);
    if (r->sub_class_of_id() == resource_class_id)
      throw Error(file_, __LINE__, fmt::format(R"(ResourceClass "{}" to be removed from data model "{}" is super class of "{}"!)"s,
          static_cast<std::string>(resource_class_ptr->label().get("en")) , shortname_.to_string(), static_cast<std::string>(r->label().get("en"))));
  }
  //
  // Check if resource class is referenced by some property in the project (ToDo:: search all data models of project)
  //
  for (const auto& prop_id: properties_) {
    PropertyPtr property_ptr = ModelItem::get_item<Property>(prop_id);
    if (property_ptr->value_type() == ValueType::Link) {
      LinkPropertyPtr link_property_ptr = std::dynamic_pointer_cast<LinkProperty>(property_ptr);
      if (link_property_ptr != nullptr) {
        if (link_property_ptr->to_resource_class_id() == resource_class_id) {
          throw Error(file_, __LINE__,
              fmt::format(R"(ResourceClass "{}" is referenced by LinkValue "{}"!)"s,
                          static_cast<std::string>(resource_class_ptr->label().get("en")), static_cast<std::string>(link_property_ptr->label().get("en"))));
        }
      }
    }
  }

  resource_classes_.erase(resource_class_id);
  last_modification_date_ = xsd::DateTimeStamp();
  modified_by_ = agent_id;
  resource_class_ptr->in_data_model_ = Identifier::empty_identifier();
  resource_class_ptr->last_modification_date_ = last_modification_date_;
  resource_class_ptr->modified_by_ = agent_id;
  resource_class_ptr->notify(ObserverAction::UPDATE, resource_class_ptr); // Property's in_data_model_ changed...
  notify(ObserverAction::UPDATE, shared_from_this());
}

void DataModel::add_property(const dsp::Identifier& property_id, const dsp::Identifier &agent_id) {
  if (properties_.find(property_id) != properties_.end()) {
    throw Error(file_, __LINE__,
        fmt::format(R"(Property with id="{}" already assigned to data model "{}")"s,
            property_id.to_string(), shortname_.to_string()));
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

void DataModel::remove_property(const dsp::Identifier &property_id, const dsp::Identifier& agent_id) {
  //
  // ToDo: Check here if data model is in use!!!
  //
  auto prop = properties_.find(property_id);
  if (prop == properties_.end()) {
    throw Error(file_, __LINE__,
        fmt::format(R"(Property with id="{}" is not in data model "{}"!)"s,
            property_id.to_string(), shortname_.to_string()));
  }
  PropertyPtr property = get_item<Property>(property_id);
  //
  // Check if property is referenced as super-property
  //
  for (const auto& prop_id: properties_) {
    PropertyPtr p = dsp::ModelItem::get_item<Property>(prop_id);
    if (p->sub_property_of_id() == property_id) {
      throw Error(file_, __LINE__,
          fmt::format(R"(Property "{}" is referenced as superproperty by "{}"!)"s,
                      static_cast<std::string>(property->label().get("en")), static_cast<std::string>(p->label().get("en"))));
    }
  }
  //
  // Check if property is referenced by and ResourceClass
  //
  for (const auto& res_id: resource_classes_) {
    ResourceClassPtr resclass = dsp::ModelItem::get_item<ResourceClass>(res_id);
    if (resclass->has_properties_.find(property_id) != resclass->has_properties_.end()) {
      throw Error(file_, __LINE__,
          fmt::format(R"(Property "{}" is referenced in ResourceClass.)"s,
                      static_cast<std::string>(property->label().get("en")), static_cast<std::string>(resclass->label().get("en"))));
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