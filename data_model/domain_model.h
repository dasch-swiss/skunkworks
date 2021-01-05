//
// Created by Lukas Rosenthaler on 02.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_DOMAIN_MODEL_H_
#define SKUNKWORKS_DATA_MODEL_DOMAIN_MODEL_H_

#include <string>
#include <unordered_map>

#include "agent.h"
#include "project.h"
#include "key_value_store.h"
#include "adapter.h"

namespace dsp {

template<typename T>
class DomainModel {
 public:
  DomainModel(const std::shared_ptr<KeyValueStore> &store, const std::shared_ptr<Adapter<T>> &adapter) : store_(store), adapter_(adapter) {}

  std::shared_ptr<Agent> agent(const dsp::Identifier &id);

  void agent(const std::shared_ptr<Agent> &agent);

  std::shared_ptr<Project> project(const dsp::Identifier &id);

  void project(const std::shared_ptr<Project> &project);

 private:
  std::shared_ptr<KeyValueStore> store_;
  std::shared_ptr<Adapter<T>> adapter_;
  std::unordered_map<dsp::Identifier, std::shared_ptr<Agent>> agents_;
  std::unordered_map<dsp::Identifier, std::shared_ptr<Project>> projects_;

};

}


#endif //SKUNKWORKS_DATA_MODEL_DOMAIN_MODEL_H_
