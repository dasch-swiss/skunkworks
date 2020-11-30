//
// Created by Lukas Rosenthaler on 25.11.20.
//



#include "helpers/uuid.h"
#include "value_class.h"

#include <utility>

namespace entities {

ValueClass::ValueClass(
    std::string class_label,
    std::string class_description
) :
    class_label_(std::move(class_label)),
    class_description_(std::move(class_description)) {
  id_ = uuid::generate_uuid_v4();
}

}
