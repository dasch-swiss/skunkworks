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

  SECTION("Resource class JSON tests") {
    dsp::ResourceClassPtr my_resclass = dsp::ResourceClass::Factory(
        my_agent->id(),
        xsd::LangString("en", "MyResclass-Label"),
        xsd::LangString("en", "MyResclass-Description"));
    dsp::ResourceClassPtr my_subresclass = dsp::ResourceClass::Factory(
        my_agent->id(),
        xsd::LangString("en", "MyProperty-Label"),
        xsd::LangString("en", "MyProperty-Description"),
        my_resclass->id());
    nlohmann::json json_obj = my_subresclass->to_json();


    REQUIRE(json_obj["version"].get<int>() == 1);
    REQUIRE(json_obj["type"].get<std::string>() == "ResourceClass"s);
    REQUIRE(json_obj["sub_class_of"].get<std::string>() == my_resclass->id().to_string());

    dsp::Identifier id(my_subresclass->id());
    dsp::Identifier subresclass_of(my_subresclass->sub_class_of_id());
    dsp::ModelItem::delete_item<dsp::ResourceClass>(my_subresclass);
    my_subresclass = dsp::ResourceClass::Factory(json_obj);
    REQUIRE(id == my_subresclass->id());
    REQUIRE(subresclass_of == my_subresclass->sub_class_of_id());
  }

  SECTION("Ading and removing properties") {
    dsp::ResourceClassPtr my_resclass = dsp::ResourceClass::Factory(
        my_agent->id(),
        xsd::LangString("en", "MyResclass-Label"),
        xsd::LangString("en", "MyResclass-Description"));
    REQUIRE(my_resclass->modified_by_id() == dsp::Identifier::empty_identifier());
    dsp::PropertyPtr my_property1 = dsp::Property::Factory(
        my_agent->id(),
        xsd::LangString("en", "MyProperty1-Label"),
        xsd::LangString("en", "MyProperty1-Description"),
        dsp::ValueType::SimpleText);

    dsp::PropertyPtr my_property2 = dsp::Property::Factory(
        my_agent->id(),
        xsd::LangString("en", "MyProperty1-Label"),
        xsd::LangString("en", "MyProperty1-Description"),
        dsp::ValueType::Boolean);

    my_resclass->add_property(my_property1, 0, dsp::ResourceClass::HasProperty::unlimited, my_agent);
    REQUIRE(my_resclass->modified_by_id() == my_agent->id());
    xsd::DateTimeStamp lmt(my_resclass->last_modification_date());
    dsp::ResourceClass::HasPropertiesMap props = my_resclass->has_properties();
    auto pp1 = props.find(my_property1->id());
    REQUIRE(pp1 != props.end());
    REQUIRE(pp1->first == my_property1->id());
    REQUIRE(pp1->second.min_count_ == 0);
    REQUIRE(pp1->second.max_count_ == dsp::ResourceClass::HasProperty::unlimited);

    REQUIRE_THROWS_AS(my_resclass->add_property(my_property2, 0, dsp::ResourceClass::HasProperty::unlimited, my_agent), dsp::Error);
    my_resclass->add_property(my_property2, 1, 1, my_agent);
    REQUIRE(lmt < my_resclass->last_modification_date());
    lmt = my_resclass->last_modification_date();
    props = my_resclass->has_properties();
    auto pp2 = props.find(my_property2->id());
    REQUIRE(pp2 != props.end());
    REQUIRE(pp2->first == my_property2->id());
    REQUIRE(pp2->second.min_count_ == 1);
    REQUIRE(pp2->second.max_count_ == 1);

    my_resclass->change_max_count(my_property2, 1, my_agent);
    REQUIRE(lmt < my_resclass->last_modification_date());
    lmt = my_resclass->last_modification_date();
    props = my_resclass->has_properties();
    auto pp1a = props.find(my_property2->id());
    REQUIRE(pp1a != props.end());
    REQUIRE(pp1a->first == my_property2->id());
    REQUIRE(pp1a->second.min_count_ == 1);
    REQUIRE(pp1a->second.max_count_ == 1);

    my_resclass->change_min_count(my_property2, 0, my_agent);
    REQUIRE(lmt < my_resclass->last_modification_date());
    lmt = my_resclass->last_modification_date();
    props = my_resclass->has_properties();
    auto pp2a = props.find(my_property2->id());
    REQUIRE(pp2a != props.end());
    REQUIRE(pp2a->first == my_property2->id());
    REQUIRE(pp2a->second.min_count_ == 0);
    REQUIRE(pp2a->second.max_count_ == 1);

    REQUIRE_THROWS_AS(my_resclass->change_max_count(my_property2, 5, my_agent), dsp::Error);

    my_resclass->remove_property(my_property1, my_agent);
    REQUIRE(lmt < my_resclass->last_modification_date());
    lmt = my_resclass->last_modification_date();
    props = my_resclass->has_properties();
    auto pp1b = props.find(my_property1->id());
    REQUIRE(pp1b == props.end());
  }


}
