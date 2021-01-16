//
// Created by Lukas Rosenthaler on 14.01.21.
//
#include "catch2/catch.hpp"

#include <string>
#include <memory>
#include "external/nlohmann/json.hpp"

#include "project.h"
#include "data_model.h"

using namespace std::string_literals;

class MyObserver: public dsp::Observer {
 public:
  inline std::string value() { return value_; }

  inline void update(dsp::ObserverAction action, std::shared_ptr<dsp::ModelItem> item) override {
    switch (action) {
      case dsp::ObserverAction::CREATE: value_ = "CREATE"s; break;
      case dsp::ObserverAction::READ: value_ = "READ"s; break;
      case dsp::ObserverAction::UPDATE:  value_ = "UPDATE"s; break;
      case dsp::ObserverAction::REMOVE: value_ = "REMOVE"; break;
    }
  }
 private:
  std::string value_;
};


TEST_CASE("Project", "Unit") {
  SECTION("project Unit tests") {
    dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("MyAgent"));

    SECTION("Factory method") {
      dsp::ProjectPtr my_project = dsp::Project::Factory(my_agent->id(), "4123", "MyProject");
      REQUIRE(my_project->id() == dsp::Identifier("Project", "4123"));
      REQUIRE(my_project->shortcode() == "4123");
      REQUIRE(my_project->shortname() == "MyProject");
      REQUIRE(my_project->to_string() == "shortcode=4123;shortname=MyProject");
    }

    SECTION("Adding/removing data models to project") {
      dsp::Identifier identifier("Project", "4123");
      dsp::ProjectPtr my_project = dsp::ModelItem::get_item<dsp::Project>(identifier);

      dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("data_model"));
      dsp::AgentPtr my_agent2 = dsp::Agent::Factory(dsp::Shortname("MyAgent2"));
      my_project->add_data_model(my_data_model->id(), my_agent2->id());
      REQUIRE(my_project->modified_by()->id() == my_agent2->id());
      REQUIRE(my_data_model->modified_by_id() == my_agent2->id());
      REQUIRE(my_data_model->last_modification_date() == my_project->last_modification_date());

      REQUIRE_THROWS_AS(dsp::Project::Factory(my_agent->id(), "412X", "MyProject"), xsd::Error);
      REQUIRE_THROWS_AS(dsp::Project::Factory(my_agent->id(), "4123", "-MyProject"), xsd::Error);

      dsp::DataModelPtr my_data_model2 = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("data_model2"));
      my_project->add_data_model(my_data_model2->id(), my_agent);
      std::unordered_set<dsp::Identifier> ids2 = my_project->get_data_model_ids();
      REQUIRE(ids2.find(my_data_model2->id()) != ids2.end());

      dsp::DataModelPtr my_data_model3 = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("data_model3"));
      my_project->add_data_model(my_data_model3, my_agent->id());
      std::unordered_set<dsp::Identifier> ids3 = my_project->get_data_model_ids();
      REQUIRE(ids3.find(my_data_model3->id()) != ids3.end());

      dsp::DataModelPtr my_data_model4 = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("data_model4"));
      my_project->add_data_model(my_data_model4, my_agent);
      std::unordered_set<dsp::Identifier> ids4 = my_project->get_data_model_ids();
      REQUIRE(ids4.find(my_data_model4->id()) != ids4.end());

      my_project->remove_data_model(my_data_model->id(), my_agent->id());
      std::unordered_set<dsp::Identifier> ids1 = my_project->get_data_model_ids();
      REQUIRE(ids1.find(my_data_model->id()) == ids1.end());

      my_project->remove_data_model(my_data_model2->id(), my_agent);
      ids2 = my_project->get_data_model_ids();
      REQUIRE(ids2.find(my_data_model2->id()) == ids2.end());

      my_project->remove_data_model(my_data_model3, my_agent->id());
      ids3 = my_project->get_data_model_ids();
      REQUIRE(ids3.find(my_data_model3->id()) == ids3.end());

      my_project->remove_data_model(my_data_model4, my_agent);
      ids4 = my_project->get_data_model_ids();
      REQUIRE(ids4.find(my_data_model4->id()) == ids4.end());
    }
  }

  SECTION("Unit test with JSON") {
    std::shared_ptr<MyObserver> observer1(new MyObserver());
    dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("MyAgent"), observer1);
    dsp::ProjectPtr my_project = dsp::Project::Factory(my_agent->id(), "4123", "MyProject", observer1);
    dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(
        my_agent->id(),
        dsp::Shortname("data_model"),
        observer1);
    my_project->add_data_model(my_data_model->id(), my_agent->id());
    nlohmann::json json_obj = my_project->to_json();
    REQUIRE(json_obj["version"].get<int>() == 1);
    REQUIRE(json_obj["type"].get<std::string>() == "Project"s);
    REQUIRE(json_obj["id"].get<std::string>() == static_cast<std::string>(my_project->id()));
    REQUIRE(json_obj["creation_date"].get<std::string>() == static_cast<std::string>(my_project->creation_date()));
    REQUIRE(json_obj["created_by"].get<std::string>() == static_cast<std::string>(my_agent->id()));
    REQUIRE(json_obj["shortcode"].get<std::string>() == static_cast<std::string>(my_project->shortcode()));
    REQUIRE(json_obj["shortname"].get<std::string>() == static_cast<std::string>(my_project->shortname()));
    REQUIRE(json_obj["last_modification_date"].get<std::string>() == static_cast<std::string>(my_project->last_modification_date()));
    REQUIRE(json_obj["modified_by"].get<std::string>() == static_cast<std::string>(my_project->modified_by_id()));
    dsp::Identifier id(my_project->id());
    dsp::Identifier created_by(my_project->created_by_id());
    xsd::DateTimeStamp creation_date(my_project->creation_date());
    dsp::Identifier modified_by(my_project->modified_by_id());
    xsd::DateTimeStamp last_modification_date(my_project->last_modification_date());
    dsp::Shortcode shortcode(my_project->shortcode());
    dsp::Shortname shortname(my_project->shortname());
    dsp::ModelItem::delete_item(my_project);
    my_project = dsp::Project::Factory(json_obj, observer1);
    REQUIRE(observer1->value() == "CREATE"s);
    REQUIRE(id == my_project->id());
    REQUIRE(created_by == my_project->created_by_id());
    REQUIRE(creation_date == my_project->creation_date());
    REQUIRE(modified_by == my_project->modified_by_id());
    REQUIRE(last_modification_date == my_project->last_modification_date());
    REQUIRE(shortcode == my_project->shortcode());
    REQUIRE(shortname == my_project->shortname());
  }

  SECTION("Unit with observer") {
    std::shared_ptr<MyObserver> observer1(new MyObserver());
    std::shared_ptr<MyObserver> observer2(new MyObserver());

    dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("MyAgent"), observer1);
    dsp::ProjectPtr my_project = dsp::Project::Factory(my_agent->id(), "4123", "MyProject", observer1);
    REQUIRE(observer1->value() == "CREATE");

    dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(
        my_agent->id(),
        dsp::Shortname("data_model"),
        observer2);
    REQUIRE(observer2->value() == "CREATE");
    dsp::AgentPtr my_agent2 = dsp::Agent::Factory(dsp::Shortname("MyAgent2"));
    my_project->add_data_model(my_data_model->id(), my_agent2->id());
    REQUIRE(observer1->value() == "UPDATE");
    REQUIRE(observer2->value() == "UPDATE");
    REQUIRE(my_project->modified_by()->id() == my_agent2->id());
    REQUIRE(my_data_model->modified_by_id() == my_agent2->id());
    REQUIRE(my_data_model->last_modification_date() == my_project->last_modification_date());
  }
}
