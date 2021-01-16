//
// Created by Lukas Rosenthaler on 15.01.21.
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

TEST_CASE("Property tests", "[catch2]") {
  dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("MyAgent"));
  dsp::ProjectPtr my_project = dsp::Project::Factory(my_agent->id(), "4123", "testproject");
  dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("test-model"));

  SECTION("Property unit tests") {
    dsp::PropertyPtr my_property = dsp::Property::Factory(
        my_agent->id(),
        xsd::LangString("en", "MyProperty-Label"),
        xsd::LangString("en", "MyProperty-Description"),
        dsp::ValueType::SimpleText);
    REQUIRE(static_cast<std::string>(my_property->label().get("en")) == "MyProperty-Label");
    REQUIRE(static_cast<std::string>(my_property->description().get("en")) == "MyProperty-Description");
    REQUIRE(my_property->value_type() == dsp::ValueType::SimpleText);

    dsp::PropertyPtr my_subproperty = dsp::Property::Factory(
        my_agent->id(),
        xsd::LangString("en", "MyProperty-Label"),
        xsd::LangString("en", "MyProperty-Description"),
        dsp::ValueType::SimpleText, my_property->id());
    REQUIRE(my_subproperty->sub_property_of_id() == my_property->id());
  }

  SECTION("Property JSON tests") {
    dsp::PropertyPtr my_property = dsp::Property::Factory(
        my_agent->id(),
        xsd::LangString("en", "MyProperty-Label"),
        xsd::LangString("en", "MyProperty-Description"),
        dsp::ValueType::SimpleText);
    dsp::PropertyPtr my_subproperty = dsp::Property::Factory(
        my_agent->id(),
        xsd::LangString("en", "MyProperty-Label"),
        xsd::LangString("en", "MyProperty-Description"),
        dsp::ValueType::SimpleText, my_property->id());
    nlohmann::json json_obj = my_subproperty->to_json();
    REQUIRE(json_obj["version"].get<int>() == 1);
    REQUIRE(json_obj["type"].get<std::string>() == "Property"s);
    REQUIRE(json_obj["value_type"].get<std::string>() == "SimpleText"s);
    REQUIRE(json_obj["sub_property_of"].get<std::string>() == my_property->id().to_string());

    dsp::Identifier id(my_subproperty->id());
    dsp::ValueType value_type(my_subproperty->value_type());
    dsp::Identifier subproperty_of(my_subproperty->sub_property_of_id());
    dsp::ModelItem::delete_item<dsp::Property>(my_subproperty);
    my_subproperty = dsp::Property::Factory(json_obj);
    REQUIRE(id == my_subproperty->id());
    REQUIRE(value_type == my_subproperty->value_type());
    REQUIRE(subproperty_of == my_subproperty->sub_property_of_id());
  }

}
