//
// Created by Lukas Rosenthaler on 21.12.20.
//

#include "helpers/uuid.h"
#include "configuration.h"
#include "class_obj.h"

namespace dsp {

ClassObj::ClassObj(
    std::shared_ptr<Project> project,
    std::shared_ptr<Agent> agent,
    xsd::String class_label,
    xsd::String class_description
)  : attached_to_project_(project), created_by_(agent), class_label_(class_label), class_description_(class_description) {
  configuration_ = Configuration::init();
  id_ = configuration_->resclass_prefix() + uuid::generate_uuid_v4();
  creation_date_ = xsd::DateTimeStamp(); // current timestamp
}

ClassObj::ClassObj(const xsd::AnyUri &id) : id_(id) {}

void ClassObj::class_label(const xsd::String &class_label) {
  class_label_ = class_label;
  changed_.insert("class_label");
}

void ClassObj::class_description(const xsd::String &class_description)  {
  class_description_ = class_description;
  changed_.insert("class_description");
}

}