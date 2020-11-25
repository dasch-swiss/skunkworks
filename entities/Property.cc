//
// Created by Lukas Rosenthaler on 25.11.20.
//

#include <string>

#include "helpers/uuid.h"

#include "Property.h"


namespace dsp {

    Property::Property(const std::string class_label,
                       const std::string class_description,
                       const std::shared_ptr <ResourceClass> resource_class,
                       const std::shared_ptr <ValueClass> value_class,
                       const std::shared_ptr <Property> sub_class_of) :
            class_label_(class_Label),
            class_description_(class_description),
            resource_class_(resource_class),
            value_class_(value_class),
            sub_class_of_(sub_class_of) {
        id_ = uuid::generate_uuid_v4();
    }
}