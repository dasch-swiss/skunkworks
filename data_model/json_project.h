//
// Created by Lukas Rosenthaler on 03.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_JSON_PROJECT_H_
#define SKUNKWORKS_DATA_MODEL_JSON_PROJECT_H_

#include "external/nlohmann/json.hpp"

#include "project.h"

namespace dsp {

class JsonProject {

 public:
  [[nodiscard]] nlohmann::json to_json(const Project &project) const;

  std::shared_ptr<Project> from_json(const nlohmann::json &json_obj);


};


}

#endif //SKUNKWORKS_DATA_MODEL_JSON_PROJECT_H_
