//
// Created by Lukas Rosenthaler on 21.12.20.
//

#include <sstream>
#include <vector>

#include "shared/error/error.h"
#include "domain_model.h"
#include "project.h"

static const char file_[] = __FILE__;

using namespace std::string_literals;

namespace dsp {

Project::Project() {
  id_ = Identifier();
  creation_date_ = xsd::DateTimeStamp(); // current timestamp
}

Project::Project(const std::shared_ptr<Agent> &created_by,  const dsp::Shortcode &shortcode, const dsp::Shortname &shortname) : Project() {
  created_by_ = created_by;
  shortcode_ = shortcode;
  shortname_ = shortname;
}

Project::Project(const std::shared_ptr<Agent> &created_by,  xsd::String &shortcode, const xsd::String &shortname) : Project() {
  created_by_ = created_by;
  shortcode_ = shortcode;
  shortname_ = shortname;
}

Project::Project(const std::shared_ptr<Agent> &created_by, const std::string &shortcode, const std::string &shortname) : Project() {
  created_by_ = created_by;
  shortcode_ = shortcode;
  shortname_ = shortname;
}

Project::Project(const nlohmann::json& json_obj, std::shared_ptr<DomainModel>& model) {
  if (json_obj.contains("version") && (json_obj["version"] == 1) && json_obj.contains("type") && (json_obj["type"] == "Project")) {
    if (json_obj.contains("id")) {
      id_ = dsp::Identifier(json_obj["id"]);
      if (!json_obj.contains("creation_date")) throw Error(file_, __LINE__, R"("Project" has no "creation_date")");
      creation_date_ = xsd::DateTimeStamp(json_obj["creation_date"]);

      if (!json_obj.contains("created_by")) throw Error(file_, __LINE__, R"("Project" has no "created_by")");
      dsp::Identifier created_by_id(json_obj["created_by"]);
      std::shared_ptr<Agent> created_by = model->agent(created_by_id);
      created_by_ = created_by;

      if (!json_obj.contains("shortcode")) throw Error(file_, __LINE__, R"("Project" has no "shortcode")");
      shortcode_ = json_obj["shortcode"];

      if (!json_obj.contains("shortname")) throw Error(file_, __LINE__, R"("Project" has no "shortname")");
      shortname_ = json_obj["shortname"];

      std::vector<std::string> data_model_ids = json_obj["data_models"];

      if (json_obj.contains("last_modification_date") && json_obj.contains("modified_by")) {
        last_modification_date_ = xsd::DateTimeStamp(json_obj["last_modification_date"]);
        dsp::Identifier modified_by_id(json_obj["modified_by"]);
        std::shared_ptr<Agent> modified_by = model->agent(modified_by_id);
        modified_by_ = modified_by;
      }

    } else{
      throw Error(file_, __LINE__, "Project serialization has no id.");
    }
  } else {
    throw Error(file_, __LINE__, "Object serialization not consistent.");
  }
}



void Project::add_data_model(const std::shared_ptr<DataModel> &data_model) {
  if (data_model->project() != nullptr) { // data model
    throw Error(file_, __LINE__, "Data model already assigned to project: "s + static_cast<std::string>(data_model->project()->shortname()));
  }
  try {
    std::shared_ptr<DataModel> tmp = data_models_.at(data_model->id());
    std::ostringstream ss;
    ss << "Data model \""s << data_model->shortname() << "\" (" << data_model->id() << ") already exists in project \""s <<
    shortname_ << "\"(" << id_ << ")!";
    throw (Error(file_, __LINE__, ss.str()));
  }
  catch (const std::out_of_range &err) {
    data_models_[data_model->id()] = data_model;
    data_model->project_ = shared_from_this();
    return;
  } // TODO: Use C++20 with contains ASAP!
}

std::optional<DataModelPtr> Project::get_data_model(const dsp::Identifier &data_model_id) {
  auto res = data_models_.find(data_model_id);
  if (res == data_models_.end()) {
    return {};
  } else {
    return res->second;
  }
}

std::optional<DataModelPtr> Project::remove_data_model(const dsp::Identifier &data_model_id) {
  //
  // ToDo: Check here if data model is in use!!!
  //
  auto res = data_models_.find(data_model_id);
  if (res == data_models_.end()) {
    return {};
  } else {
    data_models_.erase(data_model_id);
    DataModelPtr data_model_ptr = res->second;
    data_model_ptr->project_ = std::weak_ptr<Project>();
    return data_model_ptr;
  }
}

nlohmann::json Project::to_json() {
  std::vector<std::string> data_model_ids;
  for (auto [key, value]: data_models_) {
    data_model_ids.push_back(key);
  }
  nlohmann::json json_data_models(data_model_ids);
  nlohmann::json json_obj = {
      {"version", 1},
      {"type", "Project"},
      {"id", id_},
      {"creation_date", creation_date_},
      {"created_by", created_by_.lock()->id()},
      {"shortcode", shortcode_},
      {"shortname", shortname_},
      {"data_models", json_data_models}
  };
  if (!modified_by_.expired()) {
    json_obj["last_modification_date"] = last_modification_date_;
    json_obj["modified_by"] = modified_by_.lock()->id();
  }
  return json_obj;
}

}