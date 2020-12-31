//
// Created by Lukas Rosenthaler on 21.12.20.
//

#include <sstream>

#include "project.h"

#include "shared/uuid.h"
#include "shared/error/error.h"

static const char file_[] = __FILE__;

namespace dsp {

Project::Project() {
  id_ = Id();
  creation_date_ = xsd::DateTimeStamp(); // current timestamp
}

Project::Project(const std::shared_ptr<Agent> &created_by,  dsp::Shortcode &shortcode, const dsp::Shortname &shortname) : Project() {
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


void Project::add_data_model(const std::shared_ptr<DataModel> &data_model) {
  if (data_model->project() != nullptr) { // data model
    throw Error(file_, __LINE__, "Data model already assigned to project: " + static_cast<std::string>(data_model->project()->shortname()));
  }
  try {
    std::shared_ptr<DataModel> tmp = data_models_.at(data_model->id());
    std::ostringstream ss;
    ss << "Data model \"" << data_model->shortname() << "\" (" << data_model->id() << ") already exists in project \"" <<
    shortname_ << "\"(" << id_ << ")!";
    throw (Error(file_, __LINE__, ss.str()));
  }
  catch (const std::out_of_range &err) {
    data_models_[data_model->id()] = data_model;
    data_model->project_ = shared_from_this();
    return;
  } // TODO: Use C++20 with contains ASAP!
}

std::optional<DataModelPtr> Project::get_data_model(const dsp::Id &data_model_id) {
    auto res = data_models_.find(data_model_id);
    if (res == data_models_.end()) {
      return {};
    } else {
      return res->second;
    }
}

std::optional<DataModelPtr> Project::remove_data_model(const dsp::Id &data_model_id) {
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


}