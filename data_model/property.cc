//
// Created by Lukas Rosenthaler on 25.11.20.
//

#include <string>

#include "shared/error/error.h"
#include "shared/dsp_types/identifier.h"
#include "property.h"
#include "project.h"


const char file_[] = __FILE__;

namespace dsp {

class ResourceClass;

Property::Property(const dsp::Identifier& created_by,
                   const xsd::LangString &label,
                   const xsd::LangString &description,
                   ValueType value_type,
                   const dsp::Identifier& sub_property_of) : ClassObj(created_by, dsp::Identifier::empty_identifier(), label, description),
    value_type_(value_type),
    sub_property_of_(sub_property_of) { }

std::shared_ptr<Property> Property::Factory(
    const dsp::Identifier& created_by,
    const xsd::LangString &label,
    const xsd::LangString &description,
    ValueType value_type,
    const dsp::Identifier& sub_property_of) {
  std::shared_ptr<Property> tmp(new Property(created_by, label, description, value_type, sub_property_of));
  tmp->add_item<Property>();
  return tmp;

}

Property::Property(const nlohmann::json& json_obj) : ClassObj(json_obj) {
  if (json_obj.contains("type") && (json_obj["type"] == "Property")) {
    value_type_ = json_obj["value_type"].get<ValueType>();
    if (json_obj.contains("sub_property_of")) {
      sub_property_of_ = json_obj["sub_property_of"].get<std::string>();
    } else {
      sub_property_of_ = dsp::Identifier::empty_identifier();
    }
  } else {
    throw Error(file_, __LINE__, R"("Property" serialization not consistent.)");
  }
}

std::shared_ptr<Property> Property::Factory(const nlohmann::json& json_obj) {
  std::shared_ptr<Property> tmp(new Property(json_obj)); // construct Agent object using private constructor
  if (ModelItem::item_exists(tmp->id())) { //
    throw Error(file_, __LINE__, R"("Property" with same "id" already exists!)");
  }
  tmp->add_item<Property>();
  return tmp;
}

bool Property::operator==(const Property& other) {
  return ClassObj::operator==(other) && value_type_ == other.value_type_ && sub_property_of_== other.sub_property_of_;
}

nlohmann::json Property::to_json() {
  nlohmann::json json_obj = ClassObj::to_json();
  json_obj["value_type"] = value_type_;
  if (sub_property_of_ != dsp::Identifier::empty_identifier()) json_obj["sub_property_of"] = sub_property_of_;
  return json_obj;
}

}