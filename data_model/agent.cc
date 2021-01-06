//
// Created by Lukas Rosenthaler on 27.11.20.
//

#include "shared/error/error.h"
#include "agent.h"

static const char file_[] = __FILE__;

namespace dsp {

Agent::Agent() {
  id_ = Identifier();
}

Agent::Agent(const nlohmann::json& json_obj) {
  if (json_obj.contains("version") && (json_obj["version"] == 1) && json_obj.contains("type") && (json_obj["type"] == "Agent")) {
    if (json_obj.contains("id")) {
      id_ = dsp::Identifier(json_obj["id"]);
    } else{
      throw Error(file_, __LINE__, "Agent serialization has no id.");
    }
  } else {
    throw Error(file_, __LINE__, "Object serialization not consistent.");
  }
}

nlohmann::json Agent::to_json() {
  nlohmann::json json_obj = {
      {"version", 1},
      {"type", "Agent"},
      {"id", id_.to_string()}
  };
  return json_obj;
}

}