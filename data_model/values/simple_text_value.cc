//
// Created by Lukas Rosenthaler on 19.12.20.
//

#include "simple_text_value.h"

const char file_[] = __FILE__;

namespace dsp {

std::shared_ptr<SimpleTextValue> SimpleTextValue::Factory(
    const xsd::String &text,
    const Identifier &created_by_id,
    std::shared_ptr<dsp::Observer> obs) {
  std::shared_ptr<SimpleTextValue> tmp(new SimpleTextValue(text, created_by_id));
  if (obs) tmp->attach(obs);
  tmp->add_item<SimpleTextValue>();
  tmp->notify(dsp::ObserverAction::CREATE, tmp);
  return tmp;
}

std::shared_ptr<SimpleTextValue> SimpleTextValue::Factory(const nlohmann::json& json_obj) {
  std::shared_ptr<SimpleTextValue> tmp(new SimpleTextValue(json_obj));
}

SimpleTextValue::SimpleTextValue(const nlohmann::json &json_obj) : BaseValue(json_obj) {
  if (json_obj.contains("type") && (json_obj["type"] == "SimpleTextValue")) {
    if (json_obj.contains("text")) {
      text_ = json_obj["text"].get<std::string>();
    } else {
      throw Error(file_, __LINE__,
          fmt::format(R"("SimpleTextValue (id="{}") has no text value!)"s, id_.to_string()));
    }
  } else {
    throw Error(file_, __LINE__, R"("SimpleTextValue" serialization not consistent.)");
  }
}

}