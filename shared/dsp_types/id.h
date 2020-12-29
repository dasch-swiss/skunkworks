//
// Created by Lukas Rosenthaler on 29.12.20.
//

#ifndef SKUNKWORKS_HELPERS_DSP_TYPES_ID_H_
#define SKUNKWORKS_HELPERS_DSP_TYPES_ID_H_

#include <string>

#define UUID_SYSTEM_GENERATOR

#include "helpers/uuid.h"
#include "helpers/xsd_types/xsd_string.h"

namespace dsp {

class Id {
 public:
  Id();
  Id(const std::string uuid_str);

 private:
  xsd::String id_;
};

}


#endif //SKUNKWORKS_HELPERS_DSP_TYPES_ID_H_
