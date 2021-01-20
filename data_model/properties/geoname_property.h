//
// Created by Lukas Rosenthaler on 20.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_PROPERTIES_GEONAME_PROPERTY_H_
#define SKUNKWORKS_DATA_MODEL_PROPERTIES_GEONAME_PROPERTY_H_

#include "external/nlohmann/json.hpp"
#include "data_model/property.h"

namespace dsp {

class GeonameProperty : public Property {
 public:
  static std::shared_ptr<GeonameProperty> Factory(
      const dsp::Identifier& created_by,
      const xsd::LangString &label,
      const xsd::LangString &description,
      const dsp::Identifier& sub_property_of = dsp::Identifier::empty_identifier(),
      std::shared_ptr<Observer> obs = {}) {
    std::shared_ptr<GeonameProperty> tmp(new GeonameProperty(created_by, label, description, sub_property_of));
    if (obs) tmp->attach(obs);
    tmp->add_item<GeonameProperty>();
    tmp->notify(ObserverAction::CREATE, tmp);
    return tmp;
  }

  inline static std::shared_ptr<GeonameProperty> Factory(const nlohmann::json& json_obj, std::shared_ptr<Observer> obs = {}) {
    std::shared_ptr<GeonameProperty> tmp(new GeonameProperty(json_obj)); // construct Agent object using private constructor
    if (ModelItem::item_exists(tmp->id())) { //
      throw Error(__FILE__, __LINE__, R"("Property" with same "id" already exists!)");
    }
    if (obs) tmp->attach(obs);
    tmp->add_item<GeonameProperty>();
    tmp->notify(ObserverAction::CREATE, tmp);
    return tmp;
  }

  inline nlohmann::json to_json() override  {
    nlohmann::json  json_obj = Property::to_json();
    json_obj["type"] = "GeonameProperty";
    return json_obj;
  }

 private:
  GeonameProperty(
      const dsp::Identifier& created_by,
      const xsd::LangString &label,
      const xsd::LangString &description,
      const dsp::Identifier& sub_property_of = dsp::Identifier::empty_identifier(),
      std::shared_ptr<Observer> obs = {}) : Property(created_by, label, description, ValueType::Geoname, sub_property_of) {
  }

  inline explicit GeonameProperty(const nlohmann::json& json_obj) : Property(json_obj) {
    if (json_obj.contains("type") && (json_obj["type"] == "GeonameProperty")) {
      value_type_ = ValueType::Geoname;
    } else {
      throw Error(__FILE__, __LINE__, R"("Property" serialization not consistent.)");
    }
  }

};

using GeonamePropertyPtr = std::shared_ptr<GeonameProperty>;

}

#endif //SKUNKWORKS_DATA_MODEL_PROPERTIES_GEONAME_PROPERTY_H_
