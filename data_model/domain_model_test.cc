//
// Created by Lukas Rosenthaler on 05.01.21.
//

#include "catch2/catch.hpp"

#include <memory>
#include <utility>

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
#include "observer.h"
#include "in_mem_kv_store.h"
#include "json_mem_kv_store_adapter.h"

using namespace std::string_literals;

class MyObserver: public dsp::Observer {
 public:

  inline explicit MyObserver(std::shared_ptr<dsp::DomainModel> model): model_(std::move(model)) {};

  inline void update(dsp::ObserverAction action, std::shared_ptr<dsp::ModelItem> item) const override {
    std::string action_str;
    switch (action) {
      case dsp::ObserverAction::CREATE: {
        model_->create(item);
        break;
      }
      case dsp::ObserverAction::READ: break;
      case dsp::ObserverAction::UPDATE:  {
        model_->update(item->id(), item);
        break;
      }
      case dsp::ObserverAction::REMOVE: break;
    }
  }
 private:
  std::shared_ptr<dsp::DomainModel> model_;
};

TEST_CASE("Data model tests", "[catch2|") {
  std::shared_ptr<dsp::InMemKVStore> store = std::make_shared<dsp::InMemKVStore>();
  std::shared_ptr<dsp::JsonMemKVStoreAdapter> store_adapter = std::make_shared<dsp::JsonMemKVStoreAdapter>(store);
  std::shared_ptr<dsp::DomainModel> model = std::make_shared<dsp::DomainModel>(store_adapter);

  std::shared_ptr<MyObserver> obs1 = std::make_shared<MyObserver>(model);
  dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("myAgent"), obs1);

  dsp::Identifier agent_identifier = my_agent->id();

  dsp::ProjectPtr my_project = dsp::Project::Factory(my_agent->id(), "4123", "test-project", obs1);
  dsp::Identifier proj_id = my_project->id();
  dsp::Identifier created_by_id = my_project->created_by()->id();

  dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("my-data-model"), obs1);
  my_project->add_data_model(my_data_model->id());

  dsp::ResourceClassPtr my_resclass_1 = dsp::ResourceClass::Factory(
      my_agent->id(),
      xsd::LangString("en", "MyResclass1"),
      xsd::LangString("en", "My Resclass 1..."),
      dsp::Identifier::empty_identifier(),
      obs1);
  my_data_model->add_resource_class(my_resclass_1->id());

  dsp::PropertyPtr my_prop1 = dsp::Property::Factory(my_agent->id(),
                                                     xsd::LangString("en", "MyProperty1"),
                                                     xsd::LangString("en", "My Property 1..."),
                                                     dsp::ValueType::SimpleText,
                                                     dsp::Identifier::empty_identifier(),
                                                     obs1);
  my_data_model->add_property(my_prop1->id());

  dsp::PropertyPtr my_prop2 = dsp::Property::Factory(my_agent->id(),
                                                     xsd::LangString("en", "MyProperty2"),
                                                     xsd::LangString("en", "My Property 2..."),
                                                     dsp::ValueType::SimpleText,
                                                     dsp::Identifier::empty_identifier(),
                                                     obs1);
  my_data_model->add_property(my_prop2->id());

  my_resclass_1->add_property(my_prop1->id(), 1, 1);
  my_resclass_1->add_property(my_prop2->id(), 0, 1);

  //
  // remove my_agent, my_project and model
  //
  dsp::ModelItem::delete_item<dsp::Agent>(my_agent);
  dsp::ModelItem::delete_item<dsp::Project>(my_project);
  dsp::ModelItem::delete_item<dsp::DataModel>(my_data_model);
  dsp::ModelItem::delete_item<dsp::ResourceClass>(my_resclass_1);
  dsp::ModelItem::delete_item<dsp::Property>(my_prop1);
  dsp::ModelItem::delete_item<dsp::Property>(my_prop2);
  CHECK(dsp::ModelItem::size() == 0);
  store_adapter.reset();
  //my_project.reset();more
  model.reset();

  //
  // reread the model from the store
  //
  store_adapter = std::make_shared<dsp::JsonMemKVStoreAdapter>(store);
  model = std::make_shared<dsp::DomainModel>(store_adapter);

  dsp::AgentPtr same_agent = model->read<dsp::Agent>(agent_identifier);
  dsp::ProjectPtr same_project = model->read<dsp::Project>(proj_id);

  std::vector<dsp::DataModelPtr> data_models;
  std::vector<dsp::ResourceClassPtr> resclasses;
  std::vector<dsp::PropertyPtr> properties;
  for (const auto &id: same_project->get_data_model_ids()) {
    data_models.push_back(model->read<dsp::DataModel>(id));
    CHECK(data_models.back()->shortname() == dsp::Shortname("my-data-model"));
    for (const auto &rc_id: data_models.back()->get_resource_class_ids()) {
      resclasses.push_back(model->read<dsp::ResourceClass>(rc_id));
    }
    for (const auto &prop_id: data_models.back()->get_property_ids()) {
      properties.push_back(model->read<dsp::Property>(prop_id));
    }
  }

  CHECK(same_project->shortcode() == dsp::Shortcode("4123"));
  CHECK(same_project->shortname() == dsp::Shortname("test-project"));
  CHECK(same_project->created_by()->id() == created_by_id);


}

