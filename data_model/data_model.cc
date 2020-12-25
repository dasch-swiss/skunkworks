//
// Created by Lukas Rosenthaler on 21.12.20.
//

#include "helpers/uuid.h"
#include "data_model.h"


namespace dsp {

DataModel::DataModel(const std::string &shortname) {
  id_ = uuid::generate_uuid_v4();
  shortname_ = shortname;
}

void DataModel::add_resource_class(const std::shared_ptr<ResourceClass> &resource_class) {

}

}