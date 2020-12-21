//
// Created by Lukas Rosenthaler on 25.11.20.
//

#include <string>

#include "helpers/uuid.h"

class ResourceClass;

#include "property.h"

namespace dsp {

Property::Property(const std::string class_label,
                   const std::string class_description,
                   const std::shared_ptr<BaseValue> value_class,
                   const std::shared_ptr<Property> sub_class_of) :
    class_label_(class_label),
    class_description_(class_description),
    value_class_(value_class),
    sub_class_of_(sub_class_of) {
  id_ = uuid::generate_uuid_v4();
}

}
