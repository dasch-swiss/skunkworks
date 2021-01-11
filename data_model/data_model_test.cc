#include "catch2/catch.hpp"

#include <memory>

#include "external/nlohmann/json.hpp"

#include "shared/xsd_types/lang_string.h"
#include "shared/xsd_types/xsd_error.h"
#include "shared/error/error.h"

#include "model_item.h"
#include "project.h"
#include "agent.h"
#include "data_model.h"
#include "resource_class.h"
#include "property.h"

using namespace std::string_literals;

TEST_CASE("Data model tests", "[catch2|") {
  INFO("Agent tests...")
  dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("MyAgent"));
  dsp::Identifier identifier(my_agent->id());
  dsp::Shortname shortname(my_agent->shortname());
  nlohmann::json json_agent = my_agent->to_json();
  CHECK_THROWS_AS(dsp::Agent::Factory(json_agent), dsp::Error);
  dsp::ModelItem::delete_item<dsp::Agent>(my_agent);
  my_agent = dsp::Agent::Factory(json_agent);
  CHECK(my_agent->id() == identifier);
  CHECK(my_agent->shortname() == shortname);
  //CHECK(my_agent->id() == my_agent2->id());

  INFO("Project tests...")
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

  INFO("Data model tests...");
  dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(my_agent->id(), "test-model");
  REQUIRE(my_data_model->shortname() == "test-model");
  REQUIRE_THROWS_AS(dsp::DataModel::Factory(my_agent->id(), "-test-model"), xsd::Error);
  CHECK_NOTHROW(my_project->add_data_model(my_data_model->id()));
  REQUIRE(my_data_model->project()->id() == my_project->id());
  nlohmann::json json_data_model = my_data_model->to_json();
  dsp::Identifier id2 = my_data_model->id();
  dsp::Shortname shortname2 = my_data_model->shortname();
  dsp::ModelItem::delete_item<dsp::DataModel>(my_data_model);
  my_data_model = dsp::DataModel::Factory(json_data_model);
  CHECK(id2 == my_data_model->id());
  CHECK(shortname2 == my_data_model->shortname());

  CHECK_NOTHROW(my_data_model->project());
  REQUIRE(my_data_model->project()->id() == my_project->id());



  dsp::DataModelPtr my_data_model2 = dsp::DataModel::Factory(my_agent->id(), "test-model2");
  CHECK_NOTHROW(my_project->add_data_model(my_data_model2->id()));
  REQUIRE(my_data_model2->project()->id() == my_project->id());
  CHECK_THROWS_WITH(my_project->add_data_model(my_data_model2->id()), Catch::Matchers::Contains(std::string("Data model")));

  CHECK_NOTHROW(my_project->remove_data_model(my_data_model2->id()));
  REQUIRE(my_data_model2->project_id() == dsp::Identifier::empty_identifier());

  std::optional<dsp::DataModelPtr> pp = my_project->get_data_model(my_data_model->id());
  REQUIRE(pp.value()->id() == my_data_model->id());

  INFO("Resource tests...")
  dsp::ResourceClassPtr my_resource_class =
      dsp::ResourceClass::Factory(
          my_agent->id(),
          xsd::LangString("en", "myResourceClassLabel"),
          xsd::LangString("en", "MyResourceClassDescription"));
  REQUIRE(static_cast<std::string>(my_resource_class->label().get("en")) == "myResourceClassLabel");
  REQUIRE(static_cast<std::string>(my_resource_class->description().get("en")) == "MyResourceClassDescription");

  my_data_model->add_resource_class(my_resource_class->id());

  dsp::ResourceClassPtr my_resource_class2 =
      dsp::ResourceClass::Factory(
          my_agent->id(),
          xsd::LangString("en", "myResourceClass2Label"),
          xsd::LangString("en", "MyResourceClass2Description"));
  my_data_model->add_resource_class(my_resource_class2->id());

  std::cerr << std::setw(4) << my_data_model->to_json();
  CHECK(false);


  dsp::PropertyPtr my_property =
      dsp::Property::Factory(
          my_agent->id(),
          xsd::LangString("en", "myPropertyLabel"),
          xsd::LangString("en", "myPropertyLabel"),
          dsp::ValueType::SimpleText);
  REQUIRE(static_cast<std::string>(my_property->label().get("en")) == "myPropertyLabel");
  REQUIRE(static_cast<std::string>(my_property->description().get("en")) == "myPropertyLabel");
/*
  std::cerr << __FILE__ << "|" << __LINE__ << std::endl;

  my_data_model->add_property(my_property->id());

  std::set<dsp::Identifier> props;
  REQUIRE_NOTHROW(my_resource_class->add_property(my_property->id(), 1, 1));
  props.insert(my_property->id());

  for (const auto &hp: *my_resource_class) {
    auto tmp = props.find(hp.first);
    REQUIRE(tmp != props.end());
  }
  std::cerr << __FILE__ << "|" << __LINE__ << std::endl;
   */
}
