//
// Created by Lukas Rosenthaler on 03.01.21.
//

#include "json_serializer.h"
#include "shared/error/error.h"

static const char file_[] = __FILE__;

namespace dsp {


nlohmann::json JsonSerializer::to_json(const std::shared_ptr<Agent> &agent) const {
  nlohmann::json json_obj = {
      {"class", "Agent"},
      {"id", agent->id_},
  };
  return json_obj;
}

std::shared_ptr<Agent> &JsonSerializer::from_json(const nlohmann::json &json_obj, std::shared_ptr<Agent> &agent) {
  if (json_obj.contains("class") && (json_obj["class"] == "Agent")) {
    if (!json_obj.contains("id")) throw Error(file_, __LINE__, "Json object for Agent has no id.");
    agent->id_ = dsp::Identifier(json_obj["id"]);
  } else {
    throw dsp::Error(file_, __LINE__, "Invalid json_obj. Expected Agent serialization!");
  }
  return agent;
}

nlohmann::json JsonSerializer::to_json(const std::shared_ptr<Project> &project) const {
  nlohmann::json json_obj = {
      {"class", "Agent"},
      {"id", project->id_},
      {"creation_date"},
      {"created_by", project->created_by_.lock()->id()},
      {"shortcode", project->shortcode_},
      {"shortname", project->shortname_}
  };
  if (!project->modified_by_.expired()) {
    json_obj["last_modification_date"] = project->last_modification_date_;
    json_obj["modified_by"] = project->modified_by_.lock()->id();
  }
  return json_obj;

}

std::shared_ptr<Project> &JsonSerializer::from_json(const nlohmann::json &json_obj, std::shared_ptr<Project> &project) {
  nlohmann::json j;
  if (j.contains("class") && (j["class"] == "Project")) {
    if (!j.contains("id")) throw Error(file_, __LINE__, "Json object for project has no id.");
    project->id_ = dsp::Identifier(j["id"]);
    if (!j.contains("creation_date")) throw Error(file_, __LINE__, "Json object for project has creation_date.");
    project->creation_date_ = xsd::DateTimeStamp(j["creation_date"]);
    if (!j.contains("created_by")) throw Error(file_, __LINE__, "Json object for project has no created_by");
    dsp::Identifier created_by_id(j["created_by"]);
    // Check if Agent given by created_by_id is there and get it
    project->created_by_ = domain_model_->agent(created_by_id);
    if (j.contains("last_modification_date") && j.contains("modified_by")) {
      project->last_modification_date_ = xsd::DateTimeStamp(j["last_modification_date"]);
      dsp::Identifier modified_by_id(j["modified_by"]);
      project->modified_by_ = domain_model_->agent(modified_by_id);
    }
    if (!j.contains("shortcode")) throw Error(file_, __LINE__, "Json object for project has no shortcode.");
    project->shortcode_ = j["shortcode"];
    if (!j.contains("shortname")) throw Error(file_, __LINE__, "Json object for project has no shortname.");
    project->shortcode_ = j["shortname"];
  } else {
    throw dsp::Error(file_, __LINE__, "Invalid json object. Expected project serialization!");
  }

}

}