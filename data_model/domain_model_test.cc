//
// Created by Lukas Rosenthaler on 05.01.21.
//

#include "catch2/catch.hpp"

#include <memory>

#include "external/nlohmann/json.hpp"

#include "shared/xsd_types/lang_string.h"
#include "shared/xsd_types/xsd_error.h"
#include "shared/error/error.h"

#include "project.h"
#include "agent.h"
#include "data_model.h"
#include "resource_class.h"
#include "property.h"
#include "domain_model.h"

#include "in_mem_kv_store.h"
#include "json_mem_kv_store_adapter.h"


TEST_CASE("Data model tests", "[catch2|") {
  std::shared_ptr<dsp::InMemKVStore> store = std::make_shared<dsp::InMemKVStore>();
  std::shared_ptr<dsp::JsonMemKVStoreAdapter> store_adapter = std::make_shared<dsp::JsonMemKVStoreAdapter>(store);
  std::shared_ptr<dsp::DomainModel> model = std::make_shared<dsp::DomainModel>(store_adapter);

  dsp::AgentPtr my_agent = std::make_shared<dsp::Agent>("myAgent");
  model->create<dsp::Agent>(my_agent);
  dsp::ProjectPtr my_project = std::make_shared<dsp::Project>(my_agent->id(), "4123", "test-project");
  dsp::Identifier proj_id = my_project->id();
  model->create<dsp::Project>(my_project);
  dsp::Identifier created_by_id = my_project->created_by()->id();

  dsp::DataModelPtr my_data_model = std::make_shared<dsp::DataModel>(my_agent->id(), "my-data-model");
  model->create<dsp::DataModel>(my_data_model);
  //
  // remove my_agent, my_project and model
  //
  my_agent.reset();
  my_project.reset();
  model.reset();

  //
  // reread the model from the store
  //
  std::shared_ptr<dsp::DomainModel> new_model = std::make_shared<dsp::DomainModel>(store_adapter);

  dsp::ProjectPtr same_project = new_model->read<dsp::Project>(proj_id);

  CHECK(same_project->shortcode() == dsp::Shortcode("4123"));
  CHECK(same_project->shortname() == dsp::Shortname("test-project"));
  CHECK(same_project->created_by()->id() == created_by_id);

}

