//
// Created by Lukas Rosenthaler on 27.11.20.
//

#ifndef SKUNKWORKS_AGENT_H
#define SKUNKWORKS_AGENT_H

#include "external/nlohmann/json.hpp"

#include "shared/xsd_types/xsd_any_uri.h"
#include "shared/dsp_types/id.h"
//#include "shared/generic_object_description/generic_object_description.h"
#include "external/nlohmann/json.hpp"
namespace dsp {

class Agent {
 public:
  Agent();

  Agent(const nlohmann::json& object_description);

  [[nodiscard]] inline dsp::Identifier id() const { return id_; }

  nlohmann::json to_json();

 private:
  dsp::Identifier id_;
};

using AgentPtr = std::shared_ptr<Agent>;

}


#endif //SKUNKWORKS_AGENT_H
