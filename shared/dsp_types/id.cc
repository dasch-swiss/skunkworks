//
// Created by Lukas Rosenthaler on 29.12.20.
//

#include "id.h"
//#include "helpers/uuid.h"

namespace dsp {

Id::Id() {
  id_.add_restriction(std::make_shared<xsd::RestrictionPattern>("([a-fA-F0-9]{8}[a-fA-F0-9]{4}[a-fA-F0-9]{4}[a-fA-F0-9]{4}[a-fA-F0-9]{12})", "UUID restriction"));
  id_ = uuid::generate_uuid_v4();
}

Id::Id(const std::string uuid_str)  {
  id_.add_restriction(std::make_shared<xsd::RestrictionPattern>("([a-fA-F0-9]{8}[a-fA-F0-9]{4}[a-fA-F0-9]{4}[a-fA-F0-9]{4}[a-fA-F0-9]{12})", "UUID restriction"));
  id_ = uuid_str;
}

}