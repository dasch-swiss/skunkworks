//
// Created by Lukas Rosenthaler on 21.12.20.
//

#include "helpers/uuid.h"
#include "configuration.h"
#include "class_obj.h"

namespace dsp {

ClassObj::ClassObj(
    std::shared_ptr<DataModel> in_data_model,
    std::shared_ptr<Agent> agent,
    xsd::LangString class_label,
    xsd::LangString class_description
)  : in_data_model_(in_data_model), created_by_(agent), class_label_(class_label), class_description_(class_description) {
  configuration_ = Configuration::init();
  creation_date_ = xsd::DateTimeStamp(); // current timestamp
}

ClassObj::ClassObj(const xsd::AnyUri &id) : id_(id) {}

void ClassObj::class_label(const xsd::LangString &class_label) {
  class_label_ = class_label;
  changed_.insert("class_label");
}

void ClassObj::class_description(const xsd::LangString &class_description)  {
  class_description_ = class_description;
  changed_.insert("class_description");
}

}
