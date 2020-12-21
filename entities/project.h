//
// Created by Lukas Rosenthaler on 21.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_PROJECT_H_
#define SKUNKWORKS_ENTITIES_PROJECT_H_

#include "helpers/xsd_types/xsd_any_uri.h"

namespace dsp {

class Project {
 public:
  Project();

  inline xsd::AnyUri id() const { return id_; }

 private:
  xsd::AnyUri id_;
};

}


#endif //SKUNKWORKS_ENTITIES_PROJECT_H_
