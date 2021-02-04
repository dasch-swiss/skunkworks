//
// Created by Lukas Rosenthaler on 26.11.20.
//

#include <time.h>
#include "base_value.h"
//#include "third_party/jansson/jansson.h"

const char file_[] = __FILE__;


namespace dsp {

BaseValue::BaseValue(const dsp::Identifier &created_by) : created_by_(created_by) {
  id_ = dsp::Identifier();
  creation_date_ = xsd::DateTimeStamp();
  modified_by_ = Identifier::empty_identifier();
  deleted_by_ = Identifier::empty_identifier();
  type_ = "BaseValue";
}

BaseValue::BaseValue(const nlohmann::json& json_obj) {
  if (json_obj.contains("version") && (json_obj["version"] == 1) && json_obj.contains("type")) {
    if (!json_obj.contains("type"))
      throw Error(file_, __LINE__, R"(BaseValue serialization has no "type".)"s);
    if (!json_obj.contains("id"))
      throw Error(file_, __LINE__, R"(BaseValue serialization has no "id".)"s);
    id_ = dsp::Identifier(json_obj["id"].get<std::string>());

    if (!json_obj.contains("creation_date"))
      throw Error(file_, __LINE__, fmt::format(R"(BaseValue with id="{}" has no "creation_date")"s,
                                               id_.to_string()));
    creation_date_ = xsd::DateTimeStamp(json_obj["creation_date"].get<std::string>());

    if (!json_obj.contains("created_by"))
      throw Error(file_, __LINE__, fmt::format(R"(BaseValue with id="{}" has no "created_by")"s,
                                               id_.to_string()));
    created_by_ = dsp::Identifier(json_obj["created_by"].get<std::string>());

    if (json_obj.contains("last_modification_date") && json_obj.contains("modified_by")) {
      last_modification_date_ = xsd::DateTimeStamp(json_obj["last_modification_date"].get<std::string>());
      modified_by_ = dsp::Identifier(json_obj["modified_by"].get<std::string>());
    }

    if (json_obj.contains("delete_date") && json_obj.contains("deleted_by")) {
      delete_date_ = xsd::DateTimeStamp(json_obj["delete_date"].get<std::string>());
      deleted_by_ = dsp::Identifier(json_obj["deleted_by"].get<std::string>());
    }
    if (json_obj.contains("comment"))
      for (const auto& [lang, value]: json_obj["comment"].items()) comment_[lang] = value;
  } else {
    throw Error(file_, __LINE__, R"(BaseValue: serialization not consistent.)"s);
  }
}

void BaseValue::remove(const dsp::Identifier &deleted_by) {
  delete_date_ = xsd::DateTimeStamp{};
  deleted_by_ = deleted_by;
  notify(ObserverAction::REMOVE, shared_from_this());
}

void BaseValue::remove(const xsd::LangString& delete_comment, const Identifier &deleted_by) {
  delete_date_ = xsd::DateTimeStamp{};
  deleted_by_ = deleted_by;
  deletion_comment_ = delete_comment;
  notify(ObserverAction::REMOVE, shared_from_this());
}

void BaseValue::comment(const xsd::LangString &comment, const dsp::Identifier& modified_by) {
  comment_ = comment;
  last_modification_date_ = xsd::DateTimeStamp(); // set actual date & time
  modified_by_ = modified_by;
  notify(ObserverAction::UPDATE, shared_from_this());
}

void BaseValue::comment_add(const xsd::Language& lang, const xsd::String& text, const dsp::Identifier& modified_by) {
  comment_.add(lang, text);
  last_modification_date_ = xsd::DateTimeStamp(); // set actual date & time
  modified_by_ = modified_by;
  notify(ObserverAction::UPDATE, shared_from_this());
}

void BaseValue::comment_remove(const xsd::Language& lang, const dsp::Identifier& modified_by) {
  comment_.remove(lang);
  last_modification_date_ = xsd::DateTimeStamp(); // set actual date & time
  modified_by_ = modified_by;
  notify(ObserverAction::UPDATE, shared_from_this());
}


bool BaseValue::operator==(const BaseValue &other) {
  bool is_equal =  id_ == other.id_ && creation_date_ == other.creation_date_ && created_by_ == other.created_by_;
  if (modified_by_ != Identifier::empty_identifier()) {
    is_equal = is_equal && modified_by_ == other.modified_by_ && last_modification_date_ == other.last_modification_date_;
  }
  if (deleted_by_ != Identifier::empty_identifier()) {
    is_equal = is_equal && deleted_by_ == other.deleted_by_ && delete_date_ == other.delete_date_;
  }
  is_equal = is_equal && comment_ == other.comment_;
  // ToDo:  LangString with "==" operator
  return is_equal;
}

nlohmann::json BaseValue::to_json() {
  nlohmann::json json_obj = {
      {"version", 1},
      {"type", type_},
      {"id", id_},
      {"creation_date", creation_date_},
      {"created_by", created_by_.to_string()}
  };
  if (!comment_.empty()) {
    std::unordered_map<std::string, std::string> comment_map;
    for (const auto& [lang, text]: comment_) comment_map[lang] = text;
    json_obj["comment"] = nlohmann::json (comment_map);
  }
  if (modified_by_ != dsp::Identifier::empty_identifier()) {
    json_obj["last_modification_date"] = last_modification_date_;
    json_obj["modified_by"] = modified_by_.to_string();
  }
  if (deleted_by_ != dsp::Identifier::empty_identifier()) {
    json_obj["delete_date"] = delete_date_;
    json_obj["deleted_by"] = deleted_by_.to_string();
  }
  if (!deletion_comment_.empty()) {
    std::unordered_map<std::string, std::string> delete_comment_map;
    for (const auto& [lang, text]: deletion_comment_) delete_comment_map[lang] = text;
    json_obj["delete_comment"] = nlohmann::json (delete_comment_map);
  }
  return json_obj;
}



}