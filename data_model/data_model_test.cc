#include "catch2/catch.hpp"

#include <memory>

#include "external/nlohmann/json.hpp"

#include "shared/xsd_types/xsd_error.h"
#include "shared/error/error.h"

#include "model_item.h"
#include "observer.h"
#include "project.h"
#include "agent.h"
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

  inline void reset() { value_ = ""s; }
 private:
  std::string value_;
};

TEST_CASE("Data model tests", "[catch2|") {
  dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("MyAgent"));
  dsp::ProjectPtr my_project = dsp::Project::Factory(my_agent->id(), "4123", "testproject");

  SECTION("Data model tests...") {
    dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("test-model"));
    REQUIRE(my_data_model->shortname() == "test-model");

    INFO("Creating a data model with invalid name should fail");
    REQUIRE_THROWS_AS(dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("-test-model")), xsd::Error);

    INFO("Add data model to project and test if project_id_ is set correctly.");
    CHECK_NOTHROW(my_project->add_data_model(my_data_model, my_agent));
    REQUIRE(my_data_model->project()->id() == my_project->id());
    REQUIRE(my_data_model->project_id() == my_project->id());
  }

  SECTION("Serialization to JSON and back") {
    dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("test-model"));
    CHECK_NOTHROW(my_project->add_data_model(my_data_model, my_agent));
    nlohmann::json json_obj = my_data_model->to_json();
    REQUIRE(json_obj["version"].get<int>() == 1);
    REQUIRE(json_obj["type"].get<std::string>() == "DataModel"s);
    REQUIRE(json_obj["id"].get<std::string>() == my_data_model->id().to_string());
    REQUIRE(json_obj["shortname"].get<std::string>() == my_data_model->shortname().to_string());
    REQUIRE(json_obj["creation_date"].get<std::string>() == static_cast<std::string>(my_data_model->creation_date()));
    REQUIRE(json_obj["created_by"].get<std::string>() == my_data_model->created_by_id().to_string());

    dsp::Identifier id(my_data_model->id());
    dsp::Identifier created_by(my_data_model->created_by_id());
    xsd::DateTimeStamp creation_date(my_data_model->creation_date());
    dsp::Identifier modified_by(my_data_model->modified_by_id());
    xsd::DateTimeStamp last_modification_date(my_data_model->last_modification_date());
    dsp::Shortname shortname = my_data_model->shortname();
    dsp::ModelItem::delete_item<dsp::DataModel>(my_data_model);
    my_data_model = dsp::DataModel::Factory(json_obj);
    REQUIRE(id == my_data_model->id());
    REQUIRE(created_by == my_data_model->created_by_id());
    REQUIRE(creation_date == my_data_model->creation_date());
    REQUIRE(modified_by == my_data_model->modified_by_id());
    REQUIRE(last_modification_date == my_data_model->last_modification_date());
    REQUIRE(shortname == my_data_model->shortname());
    REQUIRE(my_agent == my_data_model->created_by());

    CHECK_NOTHROW(my_data_model->project());
    REQUIRE(my_data_model->project_id() == my_project->id());
    REQUIRE(my_data_model->project()->id() == my_project->id());
  }
  SECTION("Adding data models to projects and remove them") {
    dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("test-model"));
    CHECK_NOTHROW(my_project->add_data_model(my_data_model, my_agent));

    dsp::DataModelPtr my_data_model2 = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("test-model2"));
    CHECK_NOTHROW(my_project->add_data_model(my_data_model2->id(), my_agent));

    REQUIRE(my_data_model2->project()->id() == my_project->id());
    CHECK_THROWS_WITH(my_project->add_data_model(my_data_model2->id(), my_agent), Catch::Matchers::Contains(std::string("Data model")));

    CHECK_NOTHROW(my_project->remove_data_model(my_data_model2->id(), my_agent));
    REQUIRE(my_data_model2->project_id() == dsp::Identifier::empty_identifier());

    std::optional<dsp::DataModelPtr> pp = my_project->get_data_model(my_data_model->id());
    REQUIRE(pp.value()->id() == my_data_model->id());
  }

  SECTION("Test with observer") {
    std::shared_ptr<MyObserver> observer1(new MyObserver());
    std::shared_ptr<MyObserver> observer2(new MyObserver());
    dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("test-model"), observer1);
    REQUIRE(observer1->value() == "CREATE"s);
    dsp::ProjectPtr my_project2 = dsp::Project::Factory(my_agent->id(), "4123", "testproject2", observer2);
    REQUIRE(observer1->value() == "CREATE"s);
    my_project2->add_data_model(my_data_model, my_agent);
    REQUIRE(observer1->value() == "UPDATE"s);
    REQUIRE(observer2->value() == "UPDATE"s);
    observer1->reset();
    observer2->reset();
    REQUIRE(observer1->value() == ""s);
    REQUIRE(observer2->value() == ""s);
    my_project2->remove_data_model(my_data_model, my_agent);
    REQUIRE(observer1->value() == "UPDATE"s);
    REQUIRE(observer2->value() == "UPDATE"s);
  }

  SECTION("Test adding & removing properties") {
    std::shared_ptr<MyObserver> obs1 = std::make_shared<MyObserver>();
    std::shared_ptr<MyObserver> obs2 = std::make_shared<MyObserver>();
    std::shared_ptr<MyObserver> obs3 = std::make_shared<MyObserver>();

    dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(
        my_agent->id(),
        dsp::Shortname("test-model"),
        obs1);
    REQUIRE(obs1->value() == "CREATE"s);

    dsp::PropertyPtr my_property = dsp::Property::Factory(
        my_agent->id(),
        xsd::LangString("en", "MyProperty-Label"),
        xsd::LangString("en", "MyProperty-Description"),
        dsp::ValueType::SimpleText,
        dsp::Identifier::empty_identifier(),
        obs2);
    REQUIRE(obs2->value() == "CREATE"s);

    INFO("Checking all overloads or add_property and remove_property");
    my_data_model->add_property(my_property, my_agent);
    REQUIRE(obs1->value() == "UPDATE"s);
    REQUIRE(obs2->value() == "UPDATE"s);
    obs1->reset();
    obs2->reset();
    my_data_model->remove_property(my_property, my_agent);
    REQUIRE(obs1->value() == "UPDATE"s);
    REQUIRE(obs2->value() == "UPDATE"s);

    obs1->reset();
    obs2->reset();
    my_data_model->add_property(my_property->id(), my_agent);
    REQUIRE(obs1->value() == "UPDATE"s);
    REQUIRE(obs2->value() == "UPDATE"s);
    obs1->reset();
    obs2->reset();
    my_data_model->remove_property(my_property->id(), my_agent);
    REQUIRE(obs1->value() == "UPDATE"s);
    REQUIRE(obs2->value() == "UPDATE"s);

    obs1->reset();
    obs2->reset();
    my_data_model->add_property(my_property, my_agent->id());
    REQUIRE(obs1->value() == "UPDATE"s);
    REQUIRE(obs2->value() == "UPDATE"s);
    obs1->reset();
    obs2->reset();
    my_data_model->remove_property(my_property, my_agent->id());
    REQUIRE(obs1->value() == "UPDATE"s);
    REQUIRE(obs2->value() == "UPDATE"s);

    obs1->reset();
    obs2->reset();
    my_data_model->add_property(my_property->id(), my_agent->id());
    REQUIRE(obs1->value() == "UPDATE"s);
    REQUIRE(obs2->value() == "UPDATE"s);
    obs1->reset();
    obs2->reset();
    my_data_model->remove_property(my_property->id(), my_agent->id());

    INFO("Adding and removing properties with subproperties");
    my_data_model->add_property(my_property, my_agent);
    dsp::PropertyPtr my_subproperty = dsp::Property::Factory(
        my_agent->id(),
        xsd::LangString("en", "MyProperty-Label"),
        xsd::LangString("en", "MyProperty-Description"),
        dsp::ValueType::SimpleText,
        my_property->id(),
        obs3);
    REQUIRE(obs3->value() == "CREATE"s);
    obs1->reset();
    my_data_model->add_property(my_subproperty, my_agent);
    REQUIRE(obs1->value() == "UPDATE"s);
    REQUIRE(obs3->value() == "UPDATE"s);

    obs1->reset();
    obs2->reset();
    obs3->reset();
    REQUIRE_THROWS_AS(my_data_model->remove_property(my_property->id(), my_agent->id()), dsp::Error);
    REQUIRE_NOTHROW(my_data_model->remove_property(my_subproperty->id(), my_agent->id()));
    REQUIRE(obs1->value() == "UPDATE"s);
    REQUIRE(obs3->value() == "UPDATE"s);
    REQUIRE_NOTHROW(my_data_model->remove_property(my_property->id(), my_agent->id()));
    REQUIRE(obs2->value() == "UPDATE"s);
  }

/*
  SECTION("Test integration") {
    dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("MyAgent"));
    dsp::ProjectPtr my_project = dsp::Project::Factory(my_agent->id(), "4123", "testproject");
    dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("test-model"));
    my_project->add_data_model(my_data_model->id(), my_agent);

    dsp::ResourceClassPtr my_resource_class =
        dsp::ResourceClass::Factory(
            my_agent->id(),
            xsd::LangString("en", "myResourceClassLabel"),
            xsd::LangString("en", "MyResourceClassDescription"));

    my_data_model->add_resource_class(my_resource_class->id());
    std::cerr << std::setw(4) << my_resource_class->to_json() << std::endl;
    dsp::ResourceClassPtr my_resource_class2 =
        dsp::ResourceClass::Factory(
            my_agent->id(),
            xsd::LangString("en", "myResourceClass2Label"),
            xsd::LangString("en", "MyResourceClass2Description"));
    my_data_model->add_resource_class(my_resource_class2->id());

    dsp::PropertyPtr my_property =
        dsp::Property::Factory(
            my_agent->id(),
            xsd::LangString("en", "myPropertyLabel"),
            xsd::LangString("en", "myPropertyLabel"),
            dsp::ValueType::SimpleText);

    my_data_model->add_property(my_property->id());
    REQUIRE_NOTHROW(my_resource_class->add_property(my_property->id(), 1, 1));
    std::cerr << std::setw(4) << my_resource_class->to_json() << std::endl;

    dsp::ModelItem::delete_item<dsp::Agent>(my_agent);
    dsp::ModelItem::delete_item<dsp::Project>(my_project);
    dsp::ModelItem::delete_item<dsp::Property>(my_property);
    dsp::ModelItem::delete_item<dsp::DataModel>(my_data_model);
    dsp::ModelItem::delete_item<dsp::ResourceClass>(my_resource_class);
    dsp::ModelItem::delete_item<dsp::ResourceClass>(my_resource_class2);
    CHECK(dsp::ModelItem::size() == 0);
  }
  */
}
