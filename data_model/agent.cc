//
// Created by Lukas Rosenthaler on 27.11.20.
//

#include "agent.h"

#include "../shared/uuid.h"

namespace dsp {

Agent::Agent() {
  id_ = uuid::generate_uuid_v4();
}

}
