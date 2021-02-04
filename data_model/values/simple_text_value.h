//
// Created by Lukas Rosenthaler on 19.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_VALUES_SIMPLE_TEXT_VALUE_CLASS_H_
#define SKUNKWORKS_ENTITIES_VALUES_SIMPLE_TEXT_VALUE_CLASS_H_


#include "base_value.h"

namespace dsp {

class SimpleTextValue : public BaseValue {
 public:
  static std::shared_ptr<SimpleTextValue> Factory(
      const xsd::String& text,
      const Identifier& identifier,
      std::shared_ptr<dsp::Observer> obs = {}
      );

  static std::shared_ptr<SimpleTextValue> Factory(const nlohmann::json& json_obj);

  inline std::string to_string() {}

  inline nlohmann::json  to_json() {}

 private:
  inline SimpleTextValue(xsd::String text, Identifier agent_id) : BaseValue(agent_id), text_(text) {}

  SimpleTextValue(const nlohmann::json& json_obj);

  xsd::String text_;
};

}


#endif //SKUNKWORKS_ENTITIES_VALUES_SIMPLE_TEXT_VALUE_CLASS_H_
