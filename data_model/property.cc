//
// Created by Lukas Rosenthaler on 25.11.20.
//

#include <string>

#include "shared/error/error.h"
#include "shared/dsp_types/identifier.h"
#include "data_model.h"
#include "property.h"
#include "project.h"


const char file_[] = __FILE__;

using namespace std::string_literals;

namespace dsp {

class ResourceClass;

Property::Property(const dsp::Identifier& created_by,
                   const xsd::LangString &label,
                   const xsd::LangString &description,
                   ValueType value_type,
                   const dsp::Identifier& sub_property_of) : ClassObj(created_by, dsp::Identifier::empty_identifier(), label, description),
    value_type_(value_type),
    sub_property_of_(sub_property_of) {
  if (sub_property_of_ != Identifier::empty_identifier()) {
    PropertyPtr sub_property_ptr = ModelItem::get_item<Property>(sub_property_of_);
    if (value_type_ != sub_property_ptr->value_type())
      throw Error(file_, __LINE__, fmt::format(R"(Property "{}" ("{}") is not of same value type as superproperty "{}" ({})!)"s,
          static_cast<std::string>(label_.get("en")), id_.to_string(),
          static_cast<std::string>(sub_property_ptr->label().get("en")), sub_property_ptr->id().to_string()));
  }
  reference_to_ = Identifier::empty_identifier();
}

/*
std::shared_ptr<Property> Property::Factory(
    const dsp::Identifier& created_by,
    const xsd::LangString &label,
    const xsd::LangString &description,
    ValueType value_type,
    const dsp::Identifier& sub_property_of,
    std::shared_ptr<Observer> obs) {
  std::shared_ptr<Property> tmp(new Property(created_by, label, description, value_type, sub_property_of));
  if (obs) tmp->attach(obs);
  tmp->add_item<Property>();
  tmp->notify(ObserverAction::CREATE, tmp);
  return tmp;
}
*/

Property::Property(const nlohmann::json& json_obj) : ClassObj(json_obj) {
  if (json_obj.contains("type") ) {
    if (json_obj.contains("sub_property_of")) {
      sub_property_of_ = json_obj["sub_property_of"].get<std::string>();
    } else {
      sub_property_of_ = dsp::Identifier::empty_identifier();
    }
  } else {
    throw Error(file_, __LINE__, R"(Property serialization not consistent.)"s);
  }
}

std::shared_ptr<Property> Property::Factory(const nlohmann::json& json_obj, std::shared_ptr<Observer> obs) {
  std::shared_ptr<Property> tmp(new Property(json_obj)); // construct Agent object using private constructor
  if (ModelItem::item_exists(tmp->id())) { //
    throw Error(file_, __LINE__, fmt::format(R"(Property with same id="{}" already exists!)"s, tmp->id().to_string()));
  }
  if (obs) tmp->attach(obs);
  tmp->add_item<Property>();
  tmp->notify(ObserverAction::CREATE, tmp);
  return tmp;
}

void Property::remove(dsp::Identifier agent_id, std::shared_ptr<Observer> obs) {
  if (in_data_model_ != Identifier::empty_identifier()) {
    DataModelPtr data_model_ptr = ModelItem::get_item<DataModel>(in_data_model_);
    data_model_ptr->remove_property(id_, agent_id);
  }
  ModelItem::delete_item<Property>(shared_from_this());
  notify(ObserverAction::REMOVE, shared_from_this());
}

bool Property::operator==(const Property& other) {
  return ClassObj::operator==(other) && value_type_ == other.value_type_ && sub_property_of_== other.sub_property_of_;
}

nlohmann::json Property::to_json() {
  nlohmann::json json_obj = ClassObj::to_json();
  if (sub_property_of_ != dsp::Identifier::empty_identifier()) json_obj["sub_property_of"] = sub_property_of_;
  return json_obj;
}

}