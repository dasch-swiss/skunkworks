//
// Created by Lukas Rosenthaler on 21.12.20.
//

#include "project.h"

#include "helpers/uuid.h"

namespace dsp {

Project::Project() {
  id_ = uuid::generate_uuid_v4();
}

}