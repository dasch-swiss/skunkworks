//
// Created by Lukas Rosenthaler on 02.01.21.
//

#include "shared/error/error.h"

#include "domain_model.h"
#include "json_adapter.h"
#include "json_serializer.h"
#include "in_mem_store.h"

namespace dsp {

template<typename T>
std::shared_ptr<Agent> DomainModel<T>::agent(const dsp::Identifier &id) {
  try {
    std::shared_ptr<Agent> agent = agents_.at(id);
    return agent;
  } catch (const std::out_of_range &err) {
    JsonAdapter<Agent> tmp;
    std::shared_ptr<Agent> agent = tmp.read(id, store_);
    agents_[id] = agent;
    return agent;
  }
}

void DomainModel::agent(const std::shared_ptr<Agent> &agent) {
  JsonAdapter<Agent> tmp;

  tmp.create(agent, store_);
  agents_[agent->id()] = agent;
}

std::shared_ptr<Project> DomainModel::project(const dsp::Identifier &id) {
  try {
    std::shared_ptr<Project> project = projects_.at(id);
    return project;
  } catch (const std::out_of_range &err) {
    JsonAdapter<Project> tmp;
    std::shared_ptr<Project> project = tmp.read(id, store_);
    projects_[id] = project;
    return project;
  }
}

void DomainModel::project(const std::shared_ptr<Project> &project) {
  JsonAdapter<Project> tmp;

  tmp.create(project, store_);
  projects_[project->id()] = project;
};


}