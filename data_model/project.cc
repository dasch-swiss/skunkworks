//
// Created by Lukas Rosenthaler on 21.12.20.
//

#include <sstream>

#include "project.h"

#include "helpers/uuid.h"
#include "helpers/error.h"

static const char __file__[] = __FILE__;

namespace dsp {

Project::Project() {
  id_ = uuid::generate_uuid_v4();
  shortcode_.add_restriction(std::make_shared<xsd::RestrictionPattern>("([a-fA-F0-9]{4})"));
}

void Project::add_data_model(const std::shared_ptr<DataModel> &data_model) {
  try {
    std::shared_ptr<DataModel> tmp = data_models_.at(data_model->id());
    std::ostringstream ss;
    ss << "Data model \"" << data_model->id() << "\" already exists in project \"" << id_ << "\"!";
    throw (Error(__file__, __LINE__, ss.str()));
  }
  catch (const std::out_of_range &err) {
    data_models_[data_model->id()] = data_model;
    data_model->project_id(id_);
    return;
  } // TODO: Use C++20 with contains ASAP!
}
std::shared_ptr<DataModel> Project::get_data_model(const xsd::AnyUri &id) {
    auto res = data_models_.find(id);
    if (res == data_models_.end()) {
      return nullptr;
    } else {
      return res->second;
    }
}

std::shared_ptr<DataModel> Project::remove_data_model(const xsd::AnyUri &id) {

}


}