//
// Created by Lukas Rosenthaler on 25.11.20.
//

#include "ValueClass.h"

#include "helpers/uuid.h"

namespace dsp {
    ValueClass::ValueClass(const std::string class_label,
                           const std::string class_description) :
            class_label_(class_Label),
            class_description_(class_description) {
        id_ = uuid::generate_uuid_v4();
    }
}