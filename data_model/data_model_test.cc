#include "catch2/catch.hpp"

#include <memory>

#include "helpers/xsd_types/lang_string.h"
#include "helpers/xsd_types/xsd_error.h"
#include "helpers/error.h"

#include "project.h"
#include "agent.h"
#include "data_model.h"
#include "resource_class.h"
#include "property.h"


TEST_CASE("Simple catch2 tests", "[catch2|") {
  //CHECK_NOTHROW( throw xsd::Error("GAGA", __LINE__, "KEIN FEHLER!"));

  dsp::ProjectPtr my_project = std::make_shared<dsp::Project>("4123");
  dsp::AgentPtr my_agent = std::make_shared<dsp::Agent>();

  dsp::DataModelPtr my_data_model = std::make_shared<dsp::DataModel>("test-model");
  CHECK_NOTHROW(my_project->add_data_model(my_data_model));
  REQUIRE(my_data_model->project_id() == my_project->id());

  dsp::DataModelPtr my_data_model2 = std::make_shared<dsp::DataModel>("test-model2");
  CHECK_NOTHROW(my_project->add_data_model(my_data_model2));
  REQUIRE(my_data_model2->project_id() == my_project->id());

  //CHECK_THROWS_WITH(my_project->add_data_model(my_data_model2), Catch::Matchers::Contains(std::string("Data model")));
  try {
    my_project->add_data_model(my_data_model2);
  } catch (const dsp::Error &err) {
    std::cerr << err;
  }

  REQUIRE_THROWS_AS(my_project->add_data_model(my_data_model2),  dsp::Error);
  REQUIRE_THROWS_WITH(my_project->add_data_model(my_data_model2),  Catch::Contains("Data model"));


  std::optional<dsp::DataModelPtr> pp = my_project->get_data_model(my_data_model->id());
  REQUIRE(pp.value()->id() == my_data_model->id());

  std::shared_ptr<dsp::ResourceClass> resource_class =
      std::make_shared<dsp::ResourceClass>(
          my_data_model,
          my_agent,
          xsd::LangString("en", "myLabel"),
          xsd::LangString("en", "MyDescription"));
  my_data_model->add_resource_class(resource_class);

  std::shared_ptr<dsp::Property> my_property =
      std::make_shared<dsp::Property>(
          my_data_model,
          my_agent,
          xsd::LangString("en", "myLabel"),
          xsd::LangString("en", "MyDescription"),
          dsp::ValueType::SimpleText);

  resource_class->add_property(my_property, 1, 1);

}
