//
// Created by Lukas Rosenthaler on 16.01.21.
//
#include "catch2/catch.hpp"

#include <memory>

#include "external/nlohmann/json.hpp"

#include "shared/xsd_types/xsd_error.h"
#include "shared/error/error.h"
#include "shared/xsd_types/lang_string.h"


#include "model_item.h"
#include "observer.h"
#include "project.h"
#include "agent.h"
#include "data_model.h"
#include "property.h"

using namespace std::string_literals;

class MyObserver: public dsp::Observer {
 public:
  inline std::string value() { return value_; }

  inline void update(dsp::ObserverAction action, std::shared_ptr<dsp::ModelItem> item) override {
    switch (action) {
      case dsp::ObserverAction::CREATE: value_ = "CREATE"s; break;
      case dsp::ObserverAction::READ: value_ = "READ"s; break;
      case dsp::ObserverAction::UPDATE:  value_ = "UPDATE"s; break;
      case dsp::ObserverAction::REMOVE: value_ = "REMOVE"s; break;
    }
  }

  inline void reset() { value_ = ""s; }
 private:
  std::string value_;
};

TEST_CASE("Resource class tests", "[catch2]") {
  dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("MyAgent"));
  dsp::ProjectPtr my_project = dsp::Project::Factory(my_agent->id(), "4123", "testproject");
  dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("test-model"));

  SECTION("Resource class unit tests") {
    dsp::ResourceClassPtr my_resclass = dsp::ResourceClass::Factory(
        my_agent->id(),
        xsd::LangString("en", "MyResclass-Label"),
        xsd::LangString("en", "MyResclass-Description"));
    REQUIRE(static_cast<std::string>(my_resclass->label().get("en")) == "MyResclass-Label");
    REQUIRE(static_cast<std::string>(my_resclass->description().get("en")) == "MyResclass-Description");

    dsp::ResourceClassPtr my_subresclass = dsp::ResourceClass::Factory(
        my_agent->id(),
        xsd::LangString("en", "MyProperty-Label"),
        xsd::LangString("en", "MyProperty-Description"),
        my_resclass->id());
    REQUIRE(my_subresclass->sub_class_of_id() == my_resclass->id());
  }

}
