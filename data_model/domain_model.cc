//
// Created by Lukas Rosenthaler on 02.01.21.
//

#include "shared/error/error.h"
#include "shared/generic_object_description/generic_object_description.h"

#include "domain_model.h"


namespace dsp {

std::shared_ptr<Agent> DomainModel::agent(const dsp::Identifier &id) {
  try {
    std::shared_ptr<Agent> agent = agents_.at(id);
    return agent;
  } catch (const std::out_of_range &err) {
    GenericObjectDescription obj = store_adapter->read(id);
    Agent agent(obj);
    std::shared_ptr<Agent> agent_ptr = std::make_shared<Agent>(agent);
    agents_[id] = agent_ptr;
    return agent_ptr;
  }
}

void DomainModel::agent(const std::shared_ptr<Agent> &agent) {
  GenericObjectDescription obj = agent->get_generic_object_description();
  store_adapter->create(obj);
  agents_[agent->id()] = agent;
}

std::shared_ptr<Project> DomainModel::project(const dsp::Identifier &id) {
  try {
    std::shared_ptr<Project> project = projects_.at(id);
    return project;
  } catch (const std::out_of_range &err) {
    GenericObjectDescription obj = store_adapter->read(id);
    Project project(obj);
    std::shared_ptr<Project> project_ptr = std::make_shared<Project>(project);
    projects_[id] = project_ptr;
    return project_ptr;
  }
}

void DomainModel::project(const std::shared_ptr<Project> &project) {
  GenericObjectDescription obj = project->get_generic_object_description();
  store_adapter->create(obj);
  projects_[project->id()] = project;
};


}