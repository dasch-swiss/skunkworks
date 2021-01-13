//
// Created by Lukas Rosenthaler on 21.12.20.
//


#include <utility>

#include "class_obj.h"
#include "shared/error/error.h"

#include "data_model.h"

const char file_[] = __FILE__;

namespace dsp {

ClassObj::ClassObj(
    const dsp::Identifier& created_by,
    const dsp::Identifier& in_data_model,
    const xsd::LangString& label,
    const xsd::LangString& description
)  : created_by_(created_by), in_data_model_(in_data_model), label_(label), description_(description) {
  id_ = dsp::Identifier();
  creation_date_ = xsd::DateTimeStamp(); // current timestamp
}

ClassObj::ClassObj(const nlohmann::json &json_obj) {
  if (json_obj.contains("version") && (json_obj["version"] == 1) && json_obj.contains("type")) {
    if (json_obj.contains("id")) {
      id_ = dsp::Identifier(json_obj["id"].get<std::string>());

      if (!json_obj.contains("creation_date"))
        throw Error(file_, __LINE__, R"("Project" has no "creation_date")");
      creation_date_ = xsd::DateTimeStamp(json_obj["creation_date"].get<std::string>());

      if (!json_obj.contains("created_by"))
        throw Error(file_, __LINE__, R"("Project" has no "created_by")");
      created_by_ = dsp::Identifier(json_obj["created_by"].get<std::string>());

      if (json_obj.contains("last_modification_date") && json_obj.contains("modified_by")) {
        last_modification_date_ = xsd::DateTimeStamp(json_obj["last_modification_date"].get<std::string>());
        modified_by_ = dsp::Identifier(json_obj["modified_by"].get<std::string>());
      }
      if (!json_obj.contains("in_data_model"))
        throw Error(file_, __LINE__, R"("Project" has no "in_data_model")");
      in_data_model_ = dsp::Identifier(json_obj["in_data_model"].get<std::string>());
    } else{
      throw Error(file_, __LINE__, R"("Project" serialization has no "id".)");
    }
  } else {
    throw Error(file_, __LINE__, R"("Object" serialization not consistent.)");
  }
}

void ClassObj::label(const xsd::LangString &class_label) {
  label_ = class_label;
  notify(ObserverAction::UPDATE, shared_from_this());
}

void ClassObj::description(const xsd::LangString &class_description)  {
  description_ = class_description;
  notify(ObserverAction::UPDATE, shared_from_this());
}

nlohmann::json ClassObj::to_json() {
  std::unordered_map<std::string, std::string> label_map;
  for (auto [lang, text]: label_) label_map[lang] = text;

  std::unordered_map<std::string, std::string> description_map;
  for (auto [lang, text]: description_) description_map[lang] = text;
  nlohmann::json json_obj = {
      {"version", 1},
      {"id", id_},
      {"creation_date", creation_date_},
      {"created_by", created_by_},
      {"in_data_model", in_data_model_.to_string()},
      {"label", nlohmann::json (label_map)},
      {"description", nlohmann::json (description_map)}
  };
  return json_obj;
}

bool ClassObj::operator==(const ClassObj &other) {
  return id_ == other.id_ && creation_date_ == other.creation_date_ &&
  created_by_ == other.created_by_ && in_data_model_ == other.in_data_model_;
  // ToDo:  LangString with "==" operator
}

}