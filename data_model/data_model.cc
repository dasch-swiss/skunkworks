//
// Created by Lukas Rosenthaler on 21.12.20.
//

#include "helpers/uuid.h"
#include "helpers/error.h"

#include "data_model.h"
#include "resource_class.h"

static const char file_[] = __FILE__;

namespace dsp {

DataModel::DataModel(const std::string &shortname) {
  id_ = uuid::generate_uuid_v4();
  shortname_ = shortname;
}

void DataModel::add_resource_class(const std::shared_ptr<ResourceClass> &resource_class) {
  if (resource_class->data_model_id() != xsd::AnyUri()) {
    throw Error(file_, __LINE__, "Data model has already project_id: " + static_cast<std::string>(resource_class->data_model_id()));
  }
  try {
    ResourceClassPtr tmp = resource_classes_.at(resource_class->id());
    std::ostringstream ss;
    ss << "Resource \"" << resource_class->id() << "\" already exists in data model \"" << id_ << "\"!";
    throw (Error(file_, __LINE__, ss.str()));
  }
  catch (const std::out_of_range &err) {
    resource_classes_[resource_class->id()] = resource_class;
    resource_class->data_model_id(id_);
    return;
  } // TODO: Use C++20 with contains ASAP!

}

}