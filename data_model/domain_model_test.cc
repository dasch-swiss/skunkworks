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
#include "all_properties.h"
#include "domain_model.h"
#include "observer.h"
#include "in_mem_kv_store.h"
#include "json_mem_kv_store_adapter.h"

using namespace std::string_literals;

class MyObserver: public dsp::Observer {
 public:

  inline explicit MyObserver(std::shared_ptr<dsp::DomainModel> model): model_(std::move(model)) {};

  inline void update(dsp::ObserverAction action, std::shared_ptr<dsp::ModelItem> item) override {
    std::string action_str;
    switch (action) {
      case dsp::ObserverAction::CREATE: {
        model_->create(item);
        break;
      }
      case dsp::ObserverAction::READ: break;
      case dsp::ObserverAction::UPDATE:  {
        model_->update(item);
        break;
      }
      case dsp::ObserverAction::REMOVE: break;
    }
  }
 private:
  std::shared_ptr<dsp::DomainModel> model_;
};

TEST_CASE("Data model tests", "[catch2|") {
  INFO("Setting up a small data model");
  std::shared_ptr<dsp::InMemKVStore> store = std::make_shared<dsp::InMemKVStore>();
  std::shared_ptr<dsp::JsonMemKVStoreAdapter> store_adapter = std::make_shared<dsp::JsonMemKVStoreAdapter>(store);
  std::shared_ptr<dsp::DomainModel> model = std::make_shared<dsp::DomainModel>(store_adapter);

  std::shared_ptr<MyObserver> obs1 = std::make_shared<MyObserver>(model);
  dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("myAgent"), obs1);

  dsp::ProjectPtr my_project = dsp::Project::Factory(my_agent->id(), "4123", "test-project", obs1);
  //dsp::Identifier proj_id = my_project->id();
  //dsp::Identifier created_by_id = my_project->created_by()->id();

  dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("my-data-model"), obs1);
  my_project->add_data_model(my_data_model->id(), my_agent);

  dsp::ResourceClassPtr my_resclass_1 = dsp::ResourceClass::Factory(
      my_agent->id(),
      xsd::LangString("en", "MyResclass1"),
      xsd::LangString("en", "My Resclass 1..."),
      dsp::Identifier::empty_identifier(),
      obs1);
  my_data_model->add_resource_class(my_resclass_1->id(), my_agent);

  dsp::PropertyPtr my_prop1 = dsp::SimpleTextProperty::Factory(my_agent->id(),
                                                     xsd::LangString("en", "MyProperty1"),
                                                     xsd::LangString("en", "My Property 1..."),
                                                     dsp::Identifier::empty_identifier(),
                                                     obs1);
  my_data_model->add_property(my_prop1->id(), my_agent);

  dsp::PropertyPtr my_prop2 = dsp::SimpleTextProperty::Factory(my_agent->id(),
                                                     xsd::LangString("en", "MyProperty2"),
                                                     xsd::LangString("en", "My Property 2..."),
                                                     dsp::Identifier::empty_identifier(),
                                                     obs1);
  my_data_model->add_property(my_prop2->id(), my_agent);

  my_resclass_1->add_property(my_prop1->id(), 1, 1, my_agent);
  my_resclass_1->add_property(my_prop2->id(), 0, 1, my_agent);

  INFO("Saving agent data")
  dsp::Identifier my_agent_id = my_agent->id();
  dsp::Shortname my_agent_shortname = my_agent->shortname();

  INFO("Saving project data")
  dsp::Identifier my_project_id(my_project->id());
  dsp::Shortcode my_project_shortcode(my_project->shortcode());
  dsp::Shortname my_project_shortname(my_project->shortname());
  dsp::Identifier my_project_created_by_id(my_project->created_by_id());
  xsd::DateTimeStamp my_project_creation_date(my_project->creation_date());
  dsp::Identifier my_project_modified_by_id(my_project->modified_by_id());
  xsd::DateTimeStamp my_project_lmd(my_project->last_modification_date());

  INFO("Saving data model data")
  dsp::Identifier my_data_model_id(my_data_model->id());
  dsp::Shortname my_data_model_shortname(my_data_model->shortname());
  dsp::Identifier my_data_model_created_by_id(my_data_model->created_by_id());
  xsd::DateTimeStamp my_data_model_creation_date(my_data_model->creation_date());
  dsp::Identifier my_data_model_modified_by_id(my_data_model->modified_by_id());
  xsd::DateTimeStamp my_data_model_lmd(my_data_model->last_modification_date());

  INFO("Saving resource class data");
  dsp::Identifier my_resclass_id(my_resclass_1->id());
  xsd::LangString my_resclass_label(my_resclass_1->label());
  xsd::LangString my_resclass_description(my_resclass_1->description());
  dsp::Identifier my_resclass_created_by_id(my_resclass_1->created_by_id());
  xsd::DateTimeStamp my_resclass_creation_date(my_resclass_1->creation_date());
  dsp::Identifier my_resclass_modified_by_id(my_resclass_1->modified_by_id());
  xsd::DateTimeStamp my_resclass_lmd(my_resclass_1->last_modification_date());

  INFO("Saving properties data");
  dsp::ValueType my_prop1_value_type(my_prop1->value_type());
  dsp::Identifier my_prop1_id(my_prop1->id());
  xsd::LangString my_prop1_label(my_prop1->label());
  xsd::LangString my_prop1_description(my_prop1->description());
  dsp::Identifier my_prop1_created_by_id(my_prop1->created_by_id());
  xsd::DateTimeStamp my_prop1_creation_date(my_prop1->creation_date());
  dsp::Identifier my_prop1_modified_by_id(my_prop1->modified_by_id());
  xsd::DateTimeStamp my_prop1_lmd(my_prop1->last_modification_date());

  dsp::ValueType my_prop2_value_type(my_prop2->value_type());
  dsp::Identifier my_prop2_id(my_prop2->id());
  xsd::LangString my_prop2_label(my_prop2->label());
  xsd::LangString my_prop2_description(my_prop2->description());
  dsp::Identifier my_prop2_created_by_id(my_prop2->created_by_id());
  xsd::DateTimeStamp my_prop2_creation_date(my_prop2->creation_date());
  dsp::Identifier my_prop2_modified_by_id(my_prop2->modified_by_id());
  xsd::DateTimeStamp my_prop2_lmd(my_prop2->last_modification_date());

  //
  // remove my_agent, my_project and model
  //
  INFO("Removing items from online representation...")
  dsp::ModelItem::delete_item<dsp::Agent>(my_agent);
  dsp::ModelItem::delete_item<dsp::Project>(my_project);
  dsp::ModelItem::delete_item<dsp::DataModel>(my_data_model);
  dsp::ModelItem::delete_item<dsp::ResourceClass>(my_resclass_1);
  dsp::ModelItem::delete_item<dsp::Property>(my_prop1);
  dsp::ModelItem::delete_item<dsp::Property>(my_prop2);
  CHECK(dsp::ModelItem::size() == 0);
  store_adapter.reset();
  model.reset();

  //
  // reread the model from the store
  //
  store_adapter = std::make_shared<dsp::JsonMemKVStoreAdapter>(store);
  model = std::make_shared<dsp::DomainModel>(store_adapter);

  dsp::AgentPtr same_agent = model->read<dsp::Agent>(my_agent_id);
  SECTION("Testing reread agent data") {
    REQUIRE(same_agent->id() == my_agent_id);
    REQUIRE(same_agent->shortname() == my_agent_shortname);
  }
  dsp::ProjectPtr same_project = model->read<dsp::Project>(my_project_id);
  SECTION("Testing reread project data") {
    REQUIRE(same_project->id() == my_project_id);
    REQUIRE(same_project->shortcode() == my_project_shortcode);
    REQUIRE(same_project->shortname() == my_project_shortname);
    REQUIRE(same_project->created_by_id() == my_project_created_by_id);
    REQUIRE(same_project->creation_date() == my_project_creation_date);
    REQUIRE(same_project->modified_by_id() == my_project_modified_by_id);
    REQUIRE(same_project->last_modification_date() == my_project_lmd);
  }
  std::unordered_set<dsp::Identifier> data_models = same_project->get_data_model_ids();
  REQUIRE(data_models.find(my_data_model_id) != data_models.end());

  dsp::DataModelPtr same_data_model = model->read<dsp::DataModel>(my_data_model_id);
  SECTION("Testing reread of data model") {
    REQUIRE(same_data_model->id() == my_data_model_id);
    REQUIRE(same_data_model->shortname() == my_data_model_shortname);
    REQUIRE(same_data_model->created_by_id() == my_data_model_created_by_id);
    REQUIRE(same_data_model->creation_date() == my_data_model_creation_date);
    REQUIRE(same_data_model->modified_by_id() == my_data_model_modified_by_id);
    REQUIRE(same_data_model->last_modification_date() == my_data_model_lmd);
  }
  SECTION("Reread properties and resclasses") {
    for (const auto& prop_id: same_data_model->get_property_ids()) {
      dsp::PropertyPtr same_prop = model->read<dsp::SimpleTextProperty>(prop_id);
      if (same_prop->id() == my_prop1_id) {
        REQUIRE(same_prop->value_type() == my_prop1_value_type);
        REQUIRE(same_prop->id() == my_prop1_id);
        REQUIRE(same_prop->label() == my_prop1_label);
        REQUIRE(same_prop->description() == my_prop1_description);
        REQUIRE(same_prop->created_by_id() == my_prop1_created_by_id);
        REQUIRE(same_prop->creation_date() == my_prop1_creation_date);
        REQUIRE(same_prop->modified_by_id() == my_prop1_modified_by_id);
        REQUIRE(same_prop->last_modification_date() == my_prop1_lmd);
      } else if (same_prop->id() == my_prop2_id) {
        REQUIRE(same_prop->value_type() == my_prop2_value_type);
        REQUIRE(same_prop->id() == my_prop2_id);
        REQUIRE(same_prop->label() == my_prop2_label);
        REQUIRE(same_prop->description() == my_prop2_description);
        REQUIRE(same_prop->created_by_id() == my_prop2_created_by_id);
        REQUIRE(same_prop->creation_date() == my_prop2_creation_date);
        REQUIRE(same_prop->modified_by_id() == my_prop2_modified_by_id);
        REQUIRE(same_prop->last_modification_date() == my_prop2_lmd);

      } else {
        REQUIRE(false);
      }
    }
    for (const auto& resclass_id: same_data_model->get_resource_class_ids()) {
      dsp::ResourceClassPtr same_resclass = model->read<dsp::ResourceClass>(resclass_id);
      REQUIRE(same_resclass->id() == my_resclass_id);
      REQUIRE(same_resclass->label() == my_resclass_label);
      REQUIRE(same_resclass->description() == my_resclass_description);
      REQUIRE(same_resclass->created_by_id() == my_resclass_created_by_id);
      REQUIRE(same_resclass->creation_date() == my_resclass_creation_date);
      REQUIRE(same_resclass->modified_by_id() == my_resclass_modified_by_id);
      REQUIRE(same_resclass->last_modification_date() == my_resclass_lmd);
    }
  }


  /*
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

*/
}

