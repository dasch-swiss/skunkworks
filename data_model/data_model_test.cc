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


TEST_CASE("Data model tests", "[catch2|") {
  dsp::AgentPtr my_agent = std::make_shared<dsp::Agent>();

  INFO("Project tests...")
  dsp::ProjectPtr my_project = std::make_shared<dsp::Project>(my_agent, "4123", "testproject");
  REQUIRE(static_cast<std::string>(my_project->shortcode()) == "4123");
  REQUIRE(static_cast<std::string>(my_project->shortname()) == "testproject");

  REQUIRE_THROWS_WITH(std::make_shared<dsp::Project>(my_agent, "412X", "gaga"), Catch::Matchers::Contains(std::string("Short code restriction"))) ;
  REQUIRE_THROWS_WITH(std::make_shared<dsp::Project>(my_agent, "4122", "2gaga"), Catch::Matchers::Contains(std::string("Short name restriction"))) ;

  INFO("Data model tests...");
  dsp::DataModelPtr my_data_model = std::make_shared<dsp::DataModel>("test-model");
  REQUIRE(my_data_model->shortname() == "test-model");
  REQUIRE_THROWS_AS(std::make_shared<dsp::DataModel>("-test-model"), xsd::Error);

  CHECK_NOTHROW(my_project->add_data_model(my_data_model));
  REQUIRE(my_data_model->project()->id() == my_project->id());

  nlohmann::json j = my_project->to_json();
  std::cerr << j.dump(2) << std::endl;
  CHECK(false);

  dsp::DataModelPtr my_data_model2 = std::make_shared<dsp::DataModel>("test-model2");

  CHECK_NOTHROW(my_project->add_data_model(my_data_model2));
  REQUIRE(my_data_model2->project()->id() == my_project->id());
  CHECK_THROWS_WITH(my_project->add_data_model(my_data_model2), Catch::Matchers::Contains(std::string("Data model")));

  CHECK_NOTHROW(my_project->remove_data_model(my_data_model2->id()));
  REQUIRE(my_data_model2->project() == nullptr);

  std::optional<dsp::DataModelPtr> pp = my_project->get_data_model(my_data_model->id());
  REQUIRE(pp.value()->id() == my_data_model->id());

  dsp::ResourceClassPtr my_resource_class =
      std::make_shared<dsp::ResourceClass>(
          my_agent,
          xsd::LangString("en", "myResourceClassLabel"),
          xsd::LangString("en", "MyResourceClassDescription"));
  REQUIRE(static_cast<std::string>(my_resource_class->class_label().get("en")) == "myResourceClassLabel");
  REQUIRE(static_cast<std::string>(my_resource_class->class_description().get("en")) == "MyResourceClassDescription");

  my_data_model->add_resource_class(my_resource_class);


  dsp::PropertyPtr my_property =
      std::make_shared<dsp::Property>(
          my_agent,
          xsd::LangString("en", "myPropertyLabel"),
          xsd::LangString("en", "myPropertyLabel"),
          dsp::ValueType::SimpleText);
  REQUIRE(static_cast<std::string>(my_property->class_label().get("en")) == "myPropertyLabel");
  REQUIRE(static_cast<std::string>(my_property->class_description().get("en")) == "myPropertyLabel");

  my_data_model->add_property(my_property);

  std::set<dsp::Identifier> props;
  REQUIRE_NOTHROW(my_resource_class->add_property(my_property, 1, 1));
  props.insert(my_property->id());

  for (const auto &hp: *my_resource_class) {
    auto tmp = props.find(hp.first);
    REQUIRE(tmp != props.end());
  }

}
