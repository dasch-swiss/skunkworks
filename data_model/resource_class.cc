//
// Created by Ivan Subotic on 25/11/2020.
//

#include "helpers/uuid.h"
#include "helpers/error.h"

#include "property.h"
#include "resource_class.h"
#include "agent.h"
#include "project.h"

static const char file_[] = __FILE__;

namespace dsp {

ResourceClass::ResourceClass(
    DataModelPtr in_data_model,
    std::shared_ptr<Agent> agent,
    const xsd::LangString &class_label,
    const xsd::LangString &class_description,
    std::shared_ptr<ResourceClass> sub_class_of)
    : ClassObj(in_data_model, agent, class_label, class_description), sub_class_of_(sub_class_of) {
  Configuration *configuration = Configuration::init();
  id_ = prefix() + uuid::generate_uuid_v4();
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

}
