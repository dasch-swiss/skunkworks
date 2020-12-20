//
// Created by Ivan Subotic on 25/11/2020.
//

#include "helpers/uuid.h"
#include "helpers/error.h"

#include "property.h"
#include "resource_class.h"

static const char __file__[] = __FILE__;

namespace entities {

ResourceClass::ResourceClass(const xsd::String class_label,
                             const xsd::String class_description,
                             const std::shared_ptr<ResourceClass> sub_class_of) :
    class_label_(class_label),
    class_description_(class_description),
    sub_class_of_(sub_class_of) {
  id_.set(uuid::generate_uuid_v4());
}

void ResourceClass::add_property(const std::shared_ptr<Property> property,
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
  throw Error(__file__, __LINE__, "Property with same id already exists!");
}

}
