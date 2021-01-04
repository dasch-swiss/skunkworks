//
// Created by Lukas Rosenthaler on 21.12.20.
//

#include <sstream>

#include "shared/uuid.h"
#include "shared/error/error.h"

#include "data_model.h"
#include "resource_class.h"

static const char file_[] = __FILE__;

namespace dsp {

DataModel::DataModel() {
  shortname_.add_restriction(std::make_shared<xsd::RestrictionPattern>("([a-zA-Z_][\\w\\-]*)", "Short name restriction"));
  shortname_.add_restriction(std::make_shared<xsd::RestrictionMaxLength>(64, "Short name max length=64"));
}


DataModel::DataModel(const xsd::String &shortname) : DataModel() {
  id_ = uuid::generate_uuid_v4();
  shortname_ = shortname;
}


DataModel::DataModel(const std::string &shortname) : DataModel() {
  id_ = uuid::generate_uuid_v4();
  shortname_ = shortname;
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


}