//
// Created by Lukas Rosenthaler on 29.12.20.
//

#include "id.h"
//#include "helpers/uuid.h"

namespace dsp {

Id::Id() {
  //id_.add_restriction(std::make_shared<xsd::RestrictionPattern>("([a-fA-F0-9]{8}[a-fA-F0-9]{4}[a-fA-F0-9]{4}[a-fA-F0-9]{4}[a-fA-F0-9]{12})", "UUID restriction"));
  uuid_ = uuids::uuid_system_generator{}();
}

Id::Id(const std::string &uuid_str)  {
  uuid_ = uuids::uuid::from_string(uuid_str).value();
}

Id::Id(const std::string &base, const std::string &name) {
  uuids::uuid empty;
  uuids::uuid_name_generator gen1(empty);
  uuids::uuid base_uuid = gen1(base);
  uuids::uuid_name_generator gen2(base_uuid);
  uuid_ = gen2(name);
}


}