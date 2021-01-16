//
// Created by Lukas Rosenthaler on 21.12.20.
//

#include <sstream>
#include <vector>

#include "shared/error/error.h"
#include "project.h"

static const char file_[] = __FILE__;

using namespace std::string_literals;

namespace dsp {

Project::Project(
    const dsp::Identifier &created_by,
    const dsp::Shortcode &shortcode,
    const dsp::Shortname &shortname) : ModelItem() {
  id_ = Identifier("Project", static_cast<std::string>(shortcode));
  created_by_ = created_by;
  shortcode_ = shortcode;
  shortname_ = shortname;
  creation_date_ = xsd::DateTimeStamp(); // current timestamp
  modified_by_ = dsp::Identifier::empty_identifier();
}

std::shared_ptr<Project> Project::Factory(
    const dsp::Identifier &created_by,
    const dsp::Shortcode &shortcode,
    const dsp::Shortname &shortname,
    std::shared_ptr<Observer> obs) {
  std::shared_ptr<Project> tmp(new Project(created_by, shortcode, shortname));
  if (obs) tmp->attach(obs);
  tmp->add_item<Project>();
  tmp->notify(ObserverAction::CREATE, tmp);
  return tmp;
}

Project::Project(
    const dsp::Identifier &created_by,
    const xsd::String &shortcode,
    const xsd::String &shortname)
: Project(dsp::Identifier(created_by), dsp::Shortcode(shortcode), dsp::Shortname(shortname)) { }

std::shared_ptr<Project> Project::Factory(
    const dsp::Identifier &created_by,
    const xsd::String &shortcode,
    const xsd::String &shortname,
    std::shared_ptr<Observer> obs) {
  std::shared_ptr<Project> tmp(new Project(created_by, shortcode, shortname));
  if (obs) tmp->attach(obs);
  tmp->add_item<Project>();
  tmp->notify(ObserverAction::CREATE, tmp);
  return tmp;
}

Project::Project(const dsp::Identifier &created_by, const std::string &shortcode, const std::string &shortname)
    : Project(dsp::Identifier(created_by), dsp::Shortcode(shortcode), dsp::Shortname(shortname)) { }

std::shared_ptr<Project> Project::Factory(
    const dsp::Identifier &created_by,
    const std::string &shortcode,
    const std::string &shortname,
    std::shared_ptr<Observer> obs) {
  std::shared_ptr<Project> tmp(new Project(created_by, shortcode, shortname));
  if (obs) tmp->attach(obs);
  tmp->add_item<Project>();
  tmp->notify(ObserverAction::CREATE, tmp);
  return tmp;
}

Project::Project(const nlohmann::json& json_obj) : ModelItem() {
  if (json_obj.contains("version") && (json_obj["version"] == 1) && json_obj.contains("type") && (json_obj["type"] == "Project")) {
    if (json_obj.contains("id")) {
      id_ = dsp::Identifier(json_obj["id"].get<std::string>());
      if (!json_obj.contains("creation_date")) throw Error(file_, __LINE__, R"("Project" has no "creation_date")");
      creation_date_ = xsd::DateTimeStamp(json_obj["creation_date"].get<std::string>());

      if (!json_obj.contains("created_by")) throw Error(file_, __LINE__, R"("Project" has no "created_by")");
      created_by_ = dsp::Identifier(json_obj["created_by"].get<std::string>());

      if (!json_obj.contains("shortcode")) throw Error(file_, __LINE__, R"("Project" has no "shortcode")");
      shortcode_ = json_obj["shortcode"].get<std::string>();

      if (!json_obj.contains("shortname")) throw Error(file_, __LINE__, R"("Project" has no "shortname")");
      shortname_ = json_obj["shortname"].get<std::string>();

      std::vector<std::string> data_model_ids = json_obj["data_models"];
      data_models_ = std::unordered_set<dsp::Identifier>(data_model_ids.begin(), data_model_ids.end());

      if (json_obj.contains("last_modification_date") && json_obj.contains("modified_by")
        && (dsp::Identifier(json_obj["modified_by"].get<std::string>()) != dsp::Identifier::empty_identifier())) {
          last_modification_date_ = xsd::DateTimeStamp(json_obj["last_modification_date"].get<std::string>());
          modified_by_ = dsp::Identifier(json_obj["modified_by"].get<std::string>());
      }
    } else{
      throw Error(file_, __LINE__, R"("Project" serialization has no "id".)");
    }
  } else {
    throw Error(file_, __LINE__, R"("Object" serialization not consistent.)");
  }
}

std::shared_ptr<Project> Project::Factory(const nlohmann::json& json_obj, std::shared_ptr<Observer> obs) {
  std::shared_ptr<Project> tmp(new Project(json_obj)); // construct Agent object using private constructor
  if (ModelItem::item_exists(tmp->id())) { //
    throw Error(file_, __LINE__, R"("Project" with same "id" already exists!)");
  }
  if (obs) tmp->attach(obs);
  tmp->add_item<Project>();
  tmp->notify(ObserverAction::CREATE, tmp);
  return tmp;
}

Project::~Project() {
  //if (managed()) remove_item();
}

void Project::add_data_model(const dsp::Identifier &data_model_id, const dsp::Identifier& modified_by) {
  if (data_models_.find(data_model_id) != data_models_.end()) {
    throw Error(file_,
                __LINE__,
                R"(Data model already assigned to project "")" + static_cast<std::string>(shortcode_) + R"(".)");
  }
  data_models_.insert(data_model_id);
  std::shared_ptr<DataModel> tmp = get_item<DataModel>(data_model_id);
  last_modification_date_ = xsd::DateTimeStamp();
  modified_by_ = modified_by;
  tmp->project_ = id_;
  tmp->last_modification_date_ = last_modification_date_;
  tmp->modified_by_ = modified_by_;
  tmp->notify(ObserverAction::UPDATE, tmp); // DataModel's project_ changed...
  notify(ObserverAction::UPDATE, shared_from_this());
 }

std::optional<DataModelPtr> Project::get_data_model(const dsp::Identifier &data_model_id) {
  auto res = data_models_.find(data_model_id);
  if (res == data_models_.end()) {
    return {};
  } else {
    return get_item<DataModel>(*res);
  }
}

std::optional<DataModelPtr> Project::remove_data_model(const dsp::Identifier &data_model_id, const dsp::Identifier& modified_by) {
  //
  // ToDo: Check here if data model is in use!!!
  //
  auto res = data_models_.find(data_model_id);
  if (res == data_models_.end()) {
    return {};
  } else {
    DataModelPtr data_model_ptr = get_item<DataModel>(data_model_id);
    data_models_.erase(data_model_id);
    last_modification_date_ = xsd::DateTimeStamp();
    modified_by_ = modified_by;
    data_model_ptr->project_ = Identifier::empty_identifier();
    data_model_ptr->last_modification_date_ = last_modification_date_;
    data_model_ptr->modified_by_ = modified_by_;
    data_model_ptr->notify(ObserverAction::UPDATE, data_model_ptr); // DataModel's project_ changed...
    notify(ObserverAction::UPDATE, shared_from_this());
    return data_model_ptr;
  }
}

nlohmann::json Project::to_json() {
  std::vector<std::string> data_model_ids;
  for (const auto& id: data_models_) {
    data_model_ids.push_back(id);
  }
  nlohmann::json json_data_models(data_model_ids);
  nlohmann::json json_obj = {
      {"version", 1},
      {"type", "Project"},
      {"id", id_},
      {"creation_date", creation_date_},
      {"created_by", created_by_},
      {"shortcode", shortcode_},
      {"shortname", shortname_},
      {"data_models", json_data_models}
  };
  if (modified_by_ != dsp::Identifier::empty_identifier()) {
    json_obj["last_modification_date"] = last_modification_date_;
    json_obj["modified_by"] = modified_by_;
  }
  return json_obj;
}

}