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
  id_ = uuid::generate_uuid_v4();
  shortcode_.add_restriction(std::make_shared<xsd::RestrictionPattern>("([a-fA-F0-9]{4})"));
}

void Project::add_data_model(const std::shared_ptr<DataModel> &data_model) {
  if (data_model->project_id() != xsd::AnyUri()) {
    throw Error(file_, __LINE__, "Data model has already project_id: " + static_cast<std::string>(data_model->project_id()));
  }
  try {
    std::shared_ptr<DataModel> tmp = data_models_.at(data_model->id());
    std::ostringstream ss;
    ss << "Data model \"" << data_model->id() << "\" already exists in project \"" << id_ << "\"!";
    throw (Error(file_, __LINE__, ss.str()));
  }
  catch (const std::out_of_range &err) {
    data_models_[data_model->id()] = data_model;
    data_model->project_id(id_);
    return;
  } // TODO: Use C++20 with contains ASAP!
}

std::optional<DataModelPtr> Project::get_data_model(const xsd::AnyUri &data_model_id) {
    auto res = data_models_.find(data_model_id);
    if (res == data_models_.end()) {
      return {};
    } else {
      return res->second;
    }
}

std::optional<DataModelPtr> Project::remove_data_model(const xsd::AnyUri &data_model_id) {
  auto res = data_models_.find(data_model_id);
  if (res == data_models_.end()) {
    return {};
  } else {
    data_models_.erase(data_model_id);
    DataModelPtr data_model_ptr = res->second;
    data_model_ptr->project_id(xsd::AnyUri());
    return data_model_ptr;
  }

}


}
