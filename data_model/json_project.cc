//
// Created by Lukas Rosenthaler on 03.01.21.
//

#include "shared/error/error.h"

#include "json_project.h"

static const char file_[] = __FILE__;

using namespace std::string_literals;

namespace dsp {

static auto key_selector = [](auto pair){return pair.first;};

nlohmann::json JsonProject::to_json(const Project &project) const {
  nlohmann::json json_obj = {
      {"class", "Project"},
      {"id", project.id_},
      {"creation_date", project.creation_date_},
      {"created_by", project.created_by_.lock()->id()},
      {"shortcode", project.shortcode_},
      {"shortname", project.shortname_}
  };
  if (!is_uninitialized<Agent>(project.modified_by_)) {
    json_obj["last_modification_date"] = project.last_modification_date_;
    json_obj["modified_by"] = project.modified_by_.lock()->id();
  }
  std::vector<dsp::Identifier> data_models(project.data_models_.size());
  transform(project.data_models_.begin(), project.data_models_.end(), data_models.begin(), key_selector);
  json_obj["data_models"] = data_models;
  return json_obj;
}

std::shared_ptr<Project> JsonProject::from_json(const nlohmann::json &json_obj) {
  std::shared_ptr<Project> project;

  if (json_obj.contains("class") && (json_obj["class"] == "Project")) {
    if (!json_obj.contains("id")) throw Error(file_, __LINE__, R"(Json object missing "id".)");
    project->id_ = dsp::Identifier(json_obj["id"]);
    if (!json_obj.contains("creation_date")) throw Error(file_, __LINE__, R"(Json object missing "creation_date".)");
    project->creation_date_ = xsd::DateTimeStamp(json_obj["creation_date"]);
    if (!json_obj.contains("created_by")) throw Error(file_, __LINE__, R"(Json object missing "created_by")");
    dsp::Identifier created_by_id(json_obj["created_by"]);

  } else {
    throw dsp::Error(file_, __LINE__, "gagagagagagagagagagagaga!!! ToDo! ");
  }


}

}