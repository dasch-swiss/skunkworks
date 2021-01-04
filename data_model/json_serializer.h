//
// Created by Lukas Rosenthaler on 03.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_JSON_SERIALIZER_H_
#define SKUNKWORKS_DATA_MODEL_JSON_SERIALIZER_H_

#include <memory>
#include <string>

#include "external/nlohmann/json.hpp"

#include "agent.h"
#include "project.h"
#include "domain_model.h"

namespace dsp {

class JsonSerializer {
 public:
  inline JsonSerializer(const std::shared_ptr<DomainModel> &domain_model) : domain_model_(domain_model) {}

  nlohmann::json to_json(const std::shared_ptr<Agent> &agent) const ;

  std::shared_ptr<Agent> &from_json(const nlohmann::json &json_obj, std::shared_ptr<Agent> &agent);

  nlohmann::json to_json(const std::shared_ptr<Project> &project) const ;

  std::shared_ptr<Project> &from_json(const nlohmann::json &json_obj, std::shared_ptr<Project> &project);

 private:
  std::shared_ptr<DomainModel> domain_model_;
};


}

#endif //SKUNKWORKS_DATA_MODEL_JSON_SERIALIZER_H_
