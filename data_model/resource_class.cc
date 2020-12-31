//
// Created by Ivan Subotic on 25/11/2020.
//

#include "shared/uuid.h"
#include "shared/error/error.h"

#include "property.h"
#include "resource_class.h"
#include "agent.h"
#include "project.h"

static const char file_[] = __FILE__;

namespace dsp {

ResourceClass::ResourceClass(
    const std::shared_ptr<Agent> &agent,
    const xsd::LangString &class_label,
    const xsd::LangString &class_description,
    std::shared_ptr<ResourceClass> sub_class_of)
    : ClassObj(nullptr, agent, class_label, class_description), sub_class_of_(sub_class_of) {
  Configuration *configuration = Configuration::init();
  id_ = uuid::generate_uuid_v4();
}

void ResourceClass::add_property(const std::shared_ptr<Property> &property,
                                 int min_count,
                                 int max_count) {
  try {
    HasProperty tmp = this->has_properties_.at(property->id());
  }
  catch (const std::out_of_range &err) {
    HasProperty hp = {property, min_count, max_count};
    has_properties_[property->id()] = hp;
    return;
  } // TODO: Use C++20 with contains ASAP!
  throw Error(file_, __LINE__, "Property with same id already exists!");
}

void ResourceClass::change_min_count(const dsp::Id &property_id, int min_count) {
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
}

void ResourceClass::change_max_count(const dsp::Id &property_id, int max_count) {
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
}

}
