//
// Created by Lukas Rosenthaler on 27.11.20.
//

#ifndef SKUNKWORKS_AGENT_H
#define SKUNKWORKS_AGENT_H

#include "helpers/xsd_types/xsd_any_uri.h"

namespace dsp {

class Agent {
 public:
  Agent();

  xsd::AnyUri id() const { return id_; }

 private:
  xsd::AnyUri id_;

};

using AgentPtr = std::shared_ptr<Agent>;

}


#endif //SKUNKWORKS_AGENT_H
