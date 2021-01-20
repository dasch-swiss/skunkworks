//
// Created by Lukas Rosenthaler on 20.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_PROPERTIES_LINK_PROPERTY_H_
#define SKUNKWORKS_DATA_MODEL_PROPERTIES_LINK_PROPERTY_H_

#include "external/nlohmann/json.hpp"
#include "data_model/property.h"

namespace dsp {

class LinkProperty : public Property {
 public:
  static std::shared_ptr<LinkProperty> Factory(
      const dsp::Identifier& created_by,
      const xsd::LangString& label,
      const xsd::LangString& description,
      const dsp::Identifier& to_resclass,
      const dsp::Identifier& sub_property_of = dsp::Identifier::empty_identifier(),
      std::shared_ptr<Observer> obs = {}) {
    std::shared_ptr<LinkProperty> tmp(new LinkProperty(created_by, label, description, to_resclass, sub_property_of));
    if (obs) tmp->attach(obs);
    tmp->add_item<LinkProperty>();
    tmp->notify(ObserverAction::CREATE, tmp);
    return tmp;
  }

  inline static std::shared_ptr<LinkProperty> Factory(const nlohmann::json& json_obj, std::shared_ptr<Observer> obs = {}) {
    std::shared_ptr<LinkProperty> tmp(new LinkProperty(json_obj)); // construct Agent object using private constructor
    if (ModelItem::item_exists(tmp->id())) { //
      throw Error(__FILE__, __LINE__, R"("Property" with same "id" already exists!)");
    }
    if (obs) tmp->attach(obs);
    tmp->add_item<LinkProperty>();
    tmp->notify(ObserverAction::CREATE, tmp);
    return tmp;
  }

  inline nlohmann::json to_json() override  {
    nlohmann::json  json_obj = Property::to_json();
    json_obj["type"] = "LinkProperty";
    json_obj["to_resource_class"] = to_resource_class_.to_string();
    return json_obj;
  }


  inline Identifier to_resource_class_id() { return to_resource_class_; }

  inline ResourceClassPtr to_resource_class() {
    return ModelItem::get_item<ResourceClass>(to_resource_class_);
  }

 private:
  LinkProperty(
      const dsp::Identifier& created_by,
      const xsd::LangString& label,
      const xsd::LangString& description,
      const dsp::Identifier& to_resource_class,
      const dsp::Identifier& sub_property_of = dsp::Identifier::empty_identifier(),
      std::shared_ptr<Observer> obs = {})
      : Property(created_by, label, description, ValueType::Link, sub_property_of), to_resource_class_(to_resource_class) {
  }

  inline explicit LinkProperty(const nlohmann::json& json_obj) : Property(json_obj) {
    if (json_obj.contains("type") && (json_obj["type"] == "LinkProperty")) {
      value_type_ = ValueType::Link;
    } else {
      throw Error(__FILE__, __LINE__, R"("Property" serialization not consistent.)");
    }

    if (json_obj.contains("to_resource_class")) {
      to_resource_class_ = json_obj["to_resource_class"].get<std::string>();
    }
  }


  Identifier to_resource_class_;
};

using LinkPropertyPtr = std::shared_ptr<LinkProperty>;


}

#endif //SKUNKWORKS_DATA_MODEL_PROPERTIES_LINK_PROPERTY_H_
