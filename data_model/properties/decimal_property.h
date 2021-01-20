//
// Created by Lukas Rosenthaler on 20.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_PROPERTIES_DECIMAL_PROPERTY_H_
#define SKUNKWORKS_DATA_MODEL_PROPERTIES_DECIMAL_PROPERTY_H_

#include "external/nlohmann/json.hpp"
#include "data_model/property.h"

namespace dsp {
class DecimalProperty : public Property {
 public:
  static std::shared_ptr<DecimalProperty> Factory(
      const dsp::Identifier& created_by,
      const xsd::LangString &label,
      const xsd::LangString &description,
      const dsp::Identifier& sub_property_of = dsp::Identifier::empty_identifier(),
      std::shared_ptr<Observer> obs = {}) {
    std::shared_ptr<DecimalProperty> tmp(new DecimalProperty(created_by, label, description, sub_property_of));
    if (obs) tmp->attach(obs);
    tmp->add_item<DecimalProperty>();
    tmp->notify(ObserverAction::CREATE, tmp);
    return tmp;
  }

  inline static std::shared_ptr<DecimalProperty> Factory(const nlohmann::json& json_obj, std::shared_ptr<Observer> obs = {}) {
    std::shared_ptr<DecimalProperty> tmp(new DecimalProperty(json_obj)); // construct Agent object using private constructor
    if (ModelItem::item_exists(tmp->id())) { //
      throw Error(__FILE__, __LINE__, R"("Property" with same "id" already exists!)");
    }
    if (obs) tmp->attach(obs);
    tmp->add_item<DecimalProperty>();
    tmp->notify(ObserverAction::CREATE, tmp);
    return tmp;
  }

  inline nlohmann::json to_json() override  {
    nlohmann::json  json_obj = Property::to_json();
    json_obj["type"] = "DecimalProperty";
    return json_obj;
  }

 private:
  DecimalProperty(
      const dsp::Identifier& created_by,
      const xsd::LangString &label,
      const xsd::LangString &description,
      const dsp::Identifier& sub_property_of = dsp::Identifier::empty_identifier(),
      std::shared_ptr<Observer> obs = {}) : Property(created_by, label, description, ValueType::Decimal, sub_property_of) {
  }

  inline explicit DecimalProperty(const nlohmann::json& json_obj) : Property(json_obj) {
    if (json_obj.contains("type") && (json_obj["type"] == "DecimalProperty")) {
      value_type_ = ValueType::Decimal;
    } else {
      throw Error(__FILE__, __LINE__, R"("Property" serialization not consistent.)");
    }
  }
};

using DecimalPropertyPtr = std::shared_ptr<DecimalProperty>;

}

#endif //SKUNKWORKS_DATA_MODEL_PROPERTIES_DECIMAL_PROPERTY_H_
