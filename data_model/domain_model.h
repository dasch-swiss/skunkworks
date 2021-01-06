//
// Created by Lukas Rosenthaler on 02.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_DOMAIN_MODEL_H_
#define SKUNKWORKS_DATA_MODEL_DOMAIN_MODEL_H_

#include <string>
#include <unordered_map>

#include "agent.h"
#include "project.h"
#include "store_adapter.h"

namespace dsp {

class DomainModel {
 public:
  DomainModel(const std::shared_ptr<StoreAdapter> &store_adapter) : store_adapter(store_adapter) {}

  std::shared_ptr<Agent> agent(const dsp::Identifier &id);

  void agent(const std::shared_ptr<Agent> &agent);

  std::shared_ptr<Project> project(const dsp::Identifier &id);

  void project(const std::shared_ptr<Project> &project);

 private:
  std::shared_ptr<StoreAdapter> store_adapter;
  std::unordered_map<dsp::Identifier, std::shared_ptr<Agent>> agents_;
  std::unordered_map<dsp::Identifier, std::shared_ptr<Project>> projects_;
};

}


#endif //SKUNKWORKS_DATA_MODEL_DOMAIN_MODEL_H_
