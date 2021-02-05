//
// Created by Ivan Subotic on 25/11/2020.
//

#include "shared/error/error.h"

#include "property.h"
#include "resource_class.h"
#include "agent.h"
#include "project.h"

static const char file_[] = __FILE__;

namespace dsp {

ResourceClass::ResourceClass(
    const dsp::Identifier &created_by,
    const xsd::LangString &label,
    const xsd::LangString &description,
    const dsp::Identifier sub_class_of)
    : ClassObj(created_by, dsp::Identifier::empty_identifier(), label, description), sub_class_of_(sub_class_of) {
}

std::shared_ptr<ResourceClass> ResourceClass::ResourceClass::Factory(
    const dsp::Identifier &created_by,
    const xsd::LangString &class_label,
    const xsd::LangString &class_description,
    const dsp::Identifier sub_class_of,
    std::shared_ptr<Observer> obs) {
  std::shared_ptr<ResourceClass> tmp(new ResourceClass(created_by, class_label, class_description, sub_class_of));
  if (obs) tmp->attach(obs);
  tmp->add_item<ResourceClass>();
  tmp->notify(ObserverAction::CREATE, tmp);
  return tmp;
}

ResourceClass::ResourceClass(const nlohmann::json& json_obj) : ClassObj(json_obj) {
  if (json_obj.contains("type") && (json_obj["type"] == "ResourceClass")) {
    if (json_obj.contains("sub_class_of")) {
      sub_class_of_ = dsp::Identifier(json_obj["sub_class_of"]);
    } else {
      sub_class_of_ = dsp::Identifier::empty_identifier();
    }
    if (json_obj.contains("has_properties")) {
      nlohmann::json prop_map = json_obj["has_properties"];
      for (auto& [key , val]: prop_map.items()) {
        HasProperty has_property{
          dsp::Identifier(val["property"].get<std::string>()),
          val["min_count"].get<int>(),
          val["max_count"].get<int>()};
        has_properties_[dsp::Identifier(val["property"])] = has_property;
      }
    }
  } else {
    throw Error(file_, __LINE__, R"("ResourceClass" serialization not consistent.)");
  }
}

std::shared_ptr<ResourceClass> ResourceClass::Factory(const nlohmann::json& json_obj, std::shared_ptr<Observer> obs) {
  std::shared_ptr<ResourceClass> tmp(new ResourceClass(json_obj)); // construct Agent object using private constructor
  if (ModelItem::item_exists(tmp->id())) { //
    throw Error(file_, __LINE__, R"("ResourceClass" with same "id" already exists!)");
  }
  if (obs) tmp->attach(obs);
  tmp->add_item<ResourceClass>();
  tmp->notify(ObserverAction::CREATE, tmp);
  return tmp;
}

nlohmann::json ResourceClass::to_json() {
  nlohmann::json json_obj{ClassObj::to_json()};
  json_obj["type"] = "ResourceClass";
  if (sub_class_of_ != dsp::Identifier::empty_identifier()) json_obj["sub_class_of"] = sub_class_of_;
  nlohmann::json umap_json;
  for(auto [key, val]: has_properties_) {
    nlohmann::json tmp_json;
    tmp_json["property"] = val.property_;
    tmp_json["min_count"] = val.min_count_;
    tmp_json["max_count"] = val.max_count_;
    umap_json[val.property_] = tmp_json;
  }
  json_obj["has_properties"] = umap_json;
  return json_obj;
}

void ResourceClass::add_property(const dsp::Identifier &property_id,
                                 int min_count,
                                 int max_count) {
  try {
    HasProperty tmp = this->has_properties_.at(property_id);
  }
  catch (const std::out_of_range &err) {
    HasProperty hp = {property_id, min_count, max_count};
    has_properties_[property_id] = hp;
    notify(ObserverAction::UPDATE, shared_from_this());
    return;
  } // TODO: Use C++20 with contains ASAP!
  throw Error(file_, __LINE__, "Property with same id already exists!");
}

void ResourceClass::change_min_count(const dsp::Identifier &property_id, int min_count) {
  try {
    HasProperty tmp = has_properties_.at(property_id);
    // ToDo: Check if property is in use.
    bool in_use = false;
    if (in_use) {
      if (min_count <= tmp.min_count_) {
        tmp.min_count_ = min_count;
      } else {
        throw Error(file_, __LINE__, "Cannot make min_count more restrictive for property in use (id=" + property_id.to_string() + ")!");
      }
    } else {
      tmp.min_count_ = min_count;
    }
    has_properties_[property_id] = tmp;
  } catch (const std::out_of_range &err) {
    throw Error(file_, __LINE__, "Property with id=" + property_id.to_string() + " does not exist!");
  }
  notify(ObserverAction::UPDATE, shared_from_this());
}

void ResourceClass::change_max_count(const dsp::Identifier &property_id, int max_count) {
  try {
    HasProperty tmp = has_properties_.at(property_id);
    // ToDo: Check if property is in use.
    bool in_use = false;
    if (in_use) {
      if (max_count <= tmp.max_count_) {
        tmp.max_count_ = max_count;
      } else {
        throw Error(file_, __LINE__, "Cannot make max_count more restrictive for property in use (id=" + property_id.to_string() + ")!");
      }
    } else {
      tmp.max_count_ = max_count;
    }
    has_properties_[property_id] = tmp;
  } catch (const std::out_of_range &err) {
    throw Error(file_, __LINE__, "Property with id=" + property_id.to_string() + " does not exist!");
  }
  notify(ObserverAction::UPDATE, shared_from_this());
}

void ResourceClass::remove_property(const Identifier &property_id) {
  try {
    HasProperty tmp = has_properties_.at(property_id);
    // ToDo: Check if property is in use.
    bool in_use = false;
    if (in_use) {
      throw Error(file_, __LINE__, "Cannot remove property in use (id=" + property_id.to_string() + ")!");
    } else {
      has_properties_.erase(property_id);
    }
  } catch (const std::out_of_range &err) {
    throw Error(file_, __LINE__, "Property with id=" + property_id.to_string() + " does not exist!");
  }
  notify(ObserverAction::UPDATE, shared_from_this());
}




}
