//
// Created by Lukas Rosenthaler on 25.11.20.
//



#include "helpers/uuid.h"
#include "value_class.h"

#include <utility>

namespace entities {

ValueClass::ValueClass(const xsd::String &class_label, const xsd::String &class_description) :
    class_label_(class_label), class_description_(class_description) {
  id_ = uuid::generate_uuid_v4();
}

}
