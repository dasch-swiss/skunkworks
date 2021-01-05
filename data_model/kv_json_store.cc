//
// Created by Lukas Rosenthaler on 04.01.21.
//

#include "external/nlohmann/json.hpp"
#include "shared/generic_object_description/generic_object_description.h",

#include "kv_json_store.h"

using namespace std::string_literals;

namespace dsp {

void KVJsonStore::create(GenericObjectDescription& obj) {
  nlohmann::json json_obj;
  switch (obj.object_type()) {
    case GenericObjectDescription::ObjectType::AgentType: json_obj["object_type"] = "Agent"s; break;
    case GenericObjectDescription::ObjectType::ProjectType: json_obj["object_type"] = "Project"s; break;
    case GenericObjectDescription::ObjectType::ResourceClassType: json_obj["object_type"] = "ResourceClass"s; break;
    case GenericObjectDescription::ObjectType::PropertyType: json_obj["object_type"] = "Property"s; break;
  }
  for (const auto s: obj) {
    json_obj[s.first] = static_cast<std::string>(*s.second);
  }
}

GenericObjectDescription read(id) {

}

}