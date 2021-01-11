//
// Created by Lukas Rosenthaler on 21.12.20.
//

#include "class_obj.h"

#include <utility>

namespace dsp {

ClassObj::ClassObj(
    const std::shared_ptr<DataModel>& in_data_model,
    const std::shared_ptr<Agent>& agent,
    const xsd::LangString& class_label,
    const xsd::LangString& class_description
)  : in_data_model_(in_data_model), created_by_(agent), class_label_(class_label), class_description_(class_description) {
  creation_date_ = xsd::DateTimeStamp(); // current timestamp
}

ClassObj::ClassObj(const dsp::Identifier &id) : id_(id) {}

void ClassObj::class_label(const xsd::LangString &class_label) {
  class_label_ = class_label;
  changed_.insert("class_label");
}

void ClassObj::class_description(const xsd::LangString &class_description)  {
  class_description_ = class_description;
  changed_.insert("class_description");
}

}