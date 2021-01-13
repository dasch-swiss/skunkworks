#include "catch2/catch.hpp"

#include <memory>

#include "external/nlohmann/json.hpp"

#include "shared/xsd_types/lang_string.h"
#include "shared/xsd_types/xsd_error.h"
#include "shared/error/error.h"

#include "model_item.h"
#include "observer.h"
#include "project.h"
#include "agent.h"
#include "data_model.h"
#include "resource_class.h"
#include "property.h"

using namespace std::string_literals;

class MyObserver: public dsp::Observer {

  inline void update(dsp::ObserverAction action, std::shared_ptr<dsp::ModelItem> item) const override {
    std::string action_str;
    switch (action) {
      case dsp::ObserverAction::CREATE: action_str = "CREATE"; break;
      case dsp::ObserverAction::READ: action_str = "READ"; break;
      case dsp::ObserverAction::UPDATE: action_str = "UPDATE"; break;
      case dsp::ObserverAction::REMOVE: action_str = "REMOVE"; break;
    }
    std::cerr << "Action=" << action_str << " id=" << item->id() << std::endl;
  }
};

TEST_CASE("Data model tests", "[catch2|") {
  SECTION("Agent Unit Tests") {
    std::shared_ptr<MyObserver> obs1(std::make_shared<MyObserver>());
    dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("MyAgent"), obs1);
    dsp::Identifier identifier(my_agent->id());
    dsp::Shortname shortname(my_agent->shortname());
    nlohmann::json json_agent = my_agent->to_json();
    CHECK_THROWS_AS(dsp::Agent::Factory(json_agent), dsp::Error);
    dsp::ModelItem::delete_item<dsp::Agent>(my_agent);
    my_agent = dsp::Agent::Factory(json_agent);
    CHECK(my_agent->id() == identifier);
    CHECK(my_agent->shortname() == shortname);

    my_agent->shortname(dsp::Shortname("GAGAGAGAG"));

    dsp::ModelItem::delete_item<dsp::Agent>(my_agent);
    CHECK(dsp::ModelItem::size() == 0);
  }

  SECTION("Project Unit tests") {
    dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("MyAgent"));

    dsp::ProjectPtr my_project = dsp::Project::Factory(my_agent->id(), "4123", "testproject");
    REQUIRE(static_cast<std::string>(my_project->shortcode()) == "4123");
    REQUIRE(static_cast<std::string>(my_project->shortname()) == "testproject");
    dsp::Identifier id = my_project->id();
    dsp::Shortcode shortcode = my_project->shortcode();
    dsp::Shortname shortname1 = my_project->shortname();
    xsd::DateTimeStamp cd = my_project->creation_date();
    nlohmann::json json_project = my_project->to_json();
    dsp::ModelItem::delete_item<dsp::Project>(my_project);

    my_project = dsp::Project::Factory(json_project);
    CHECK(id == my_project->id());
    CHECK(cd == my_project->creation_date());
    CHECK(shortcode == my_project->shortcode());
    CHECK(shortname1 == my_project->shortname());

    dsp::ProjectPtr mp = dsp::ModelItem::get_item<dsp::Project>(id);
    CHECK(id == mp->id());
    CHECK(my_project->id() == mp->id());
    CHECK(cd == mp->creation_date());
    CHECK(shortcode == mp->shortcode());
    CHECK(shortname1 == mp->shortname());


    REQUIRE_THROWS_WITH(dsp::Project::Factory(my_agent->id(), "412X", "gaga"), Catch::Matchers::Contains(std::string("Short code restriction"))) ;
    REQUIRE_THROWS_WITH(dsp::Project::Factory(my_agent->id(), "4122", "2gaga"), Catch::Matchers::Contains(std::string("Short name restriction"))) ;
    dsp::ModelItem::delete_item<dsp::Agent>(my_agent);
    dsp::ModelItem::delete_item<dsp::Project>(mp);
    CHECK(dsp::ModelItem::size() == 0);
  }

  SECTION("Data model tests...") {
    dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("MyAgent"));
    dsp::ProjectPtr my_project = dsp::Project::Factory(my_agent->id(), "4123", "testproject");

    dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("test-model"));
    REQUIRE(my_data_model->shortname() == "test-model");

    INFO("Creating a data model with invalid name should fail");
    REQUIRE_THROWS_AS(dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("-test-model")), xsd::Error);

    INFO("Add data model to project.");
    CHECK_NOTHROW(my_project->add_data_model(my_data_model->id()));
    REQUIRE(my_data_model->project()->id() == my_project->id());
    REQUIRE(my_data_model->project_id() == my_project->id());

    INFO("Serialize data model...");
    nlohmann::json json_data_model = my_data_model->to_json();
    dsp::Identifier id2 = my_data_model->id();
    dsp::Shortname shortname2 = my_data_model->shortname();
    dsp::ModelItem::delete_item<dsp::DataModel>(my_data_model);
    my_data_model = dsp::DataModel::Factory(json_data_model);
    CHECK(id2 == my_data_model->id());
    CHECK(shortname2 == my_data_model->shortname());

    CHECK_NOTHROW(my_data_model->project());
    REQUIRE(my_data_model->project_id() == my_project->id());
    REQUIRE(my_data_model->project()->id() == my_project->id());

    INFO("Add second data model and remove it...");
    dsp::DataModelPtr my_data_model2 = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("test-model2"));
    CHECK_NOTHROW(my_project->add_data_model(my_data_model2->id()));
    REQUIRE(my_data_model2->project()->id() == my_project->id());
    CHECK_THROWS_WITH(my_project->add_data_model(my_data_model2->id()), Catch::Matchers::Contains(std::string("Data model")));

    CHECK_NOTHROW(my_project->remove_data_model(my_data_model2->id()));
    REQUIRE(my_data_model2->project_id() == dsp::Identifier::empty_identifier());

    std::optional<dsp::DataModelPtr> pp = my_project->get_data_model(my_data_model->id());
    REQUIRE(pp.value()->id() == my_data_model->id());

    dsp::ModelItem::delete_item<dsp::Agent>(my_agent);
    dsp::ModelItem::delete_item<dsp::Project>(my_project);
    dsp::ModelItem::delete_item<dsp::DataModel>(my_data_model);
    dsp::ModelItem::delete_item<dsp::DataModel>(my_data_model2);

    CHECK(dsp::ModelItem::size() == 0);
  }

  SECTION("Resource Unit tests...") {
    dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("MyAgent"));
    dsp::ResourceClassPtr my_resource_class =
        dsp::ResourceClass::Factory(
            my_agent->id(),
            xsd::LangString("en", "myResourceClassLabel"),
            xsd::LangString("en", "MyResourceClassDescription"));
    REQUIRE(static_cast<std::string>(my_resource_class->label().get("en")) == "myResourceClassLabel");
    REQUIRE(static_cast<std::string>(my_resource_class->description().get("en")) == "MyResourceClassDescription");
    dsp::ModelItem::delete_item<dsp::Agent>(my_agent);
    dsp::ModelItem::delete_item<dsp::ResourceClass>(my_resource_class);
    CHECK(dsp::ModelItem::size() == 0);
  }

  SECTION("Property Unit tests") {
    dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("MyAgent"));
    dsp::PropertyPtr my_property =
        dsp::Property::Factory(
            my_agent->id(),
            xsd::LangString("en", "myPropertyLabel"),
            xsd::LangString("en", "myPropertyLabel"),
            dsp::ValueType::SimpleText);
    REQUIRE(static_cast<std::string>(my_property->label().get("en")) == "myPropertyLabel");
    REQUIRE(static_cast<std::string>(my_property->description().get("en")) == "myPropertyLabel");
    dsp::ModelItem::delete_item<dsp::Agent>(my_agent);
    dsp::ModelItem::delete_item<dsp::Property>(my_property);
    CHECK(dsp::ModelItem::size() == 0);
  }

  SECTION("Test integration") {
    dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("MyAgent"));
    dsp::ProjectPtr my_project = dsp::Project::Factory(my_agent->id(), "4123", "testproject");
    dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("test-model"));
    my_project->add_data_model(my_data_model->id());

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
}
