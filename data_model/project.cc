//
// Created by Lukas Rosenthaler on 21.12.20.
//

#include <sstream>
#include <vector>

#include "shared/uuid.h"
#include "shared/error/error.h"

#include "project.h"
#include "adapter.h"

static const char file_[] = __FILE__;

using namespace std::string_literals;

namespace dsp {

Project::Project() {
  id_ = Identifier();
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

Project::Project(const GenericObjectDescription& object_description) {
  if (object_description.object_type() != GenericObjectDescription::ObjectType::ProjectType) {
    throw Error(file_, __LINE__, "GenericObjectDescription is not from \"project\" class."s);
  }
  if (!object_description.has_member("id"s))
    throw Error(file_, __LINE__, R"(GenericObjectDescription for "Project" has no "id".)"s);
  id_ = dsp::Identifier(object_description.member<xsd::String>("id"s));
  if (!object_description.has_member("creation_date"s))
    throw Error(file_, __LINE__, R"(GenericObjectDescription for "Project" has no "creation_date".)"s);
  creation_date_ = object_description.member<xsd::DateTimeStamp>("creation_date"s);
  if (!object_description.has_member("created_by"s))
    throw Error(file_, __LINE__, R"(GenericObjectDescription for "Project" has no "created_by".)"s);
  dsp::Identifier created_by_id(dsp::Identifier(object_description.member<xsd::String>("created_by"s)));
  // ToDo: get Agent with the given Id here...
  if (object_description.has_member("modified_by"s)) {
    if (!object_description.has_member("last_modification_date"s))
      throw Error(file_, __LINE__, R"(GenericObjectDescription for "Project" has no "last_modification_date".)"s);
    last_modification_date_ = object_description.member<xsd::DateTimeStamp>("last_modification_date"s);
    dsp::Identifier modified_by_id(dsp::Identifier(object_description.member<xsd::String>("modified_by"s)));
    // ToDo: get Agent with given Id here...
  }
  if (!object_description.has_member("shortcode"s))
    throw Error(file_, __LINE__, R"(GenericObjectDescription for "Project" has no "shortcode".)"s);
  shortcode_ = dsp::Shortcode(object_description.member<xsd::String>("shortcode"s))
  if (!object_description.has_member("shortname"s))
    throw Error(file_, __LINE__, R"(GenericObjectDescription for "Project" has no "shortname".)"s);
  shortcode_ = dsp::Shortcode(object_description.member<xsd::String>("shortcode"s))

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

GenericObjectDescription Project::get_generic_object_description() {
  GenericObjectDescription object_description(GenericObjectDescription::ObjectType::AgentType);
  object_description.member("id"s, id_);
  object_description.member("creation_date"s, creation_date_);
  object_description.member("created_by"s, created_by_.lock()->id());
  if (!modified_by_.expired()) {
    object_description.member("last_modification_date"s, last_modification_date_);
    object_description.member("modified_by"s, modified_by_.lock()->id());
  }
  object_description.member("shortcode"s, shortcode_);
  object_description.member("shortname"s, shortname_);
}

}