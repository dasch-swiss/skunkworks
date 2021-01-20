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
#include "resource_class.h"
#include "all_properties.h"

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
    dsp::PropertyPtr my_property = dsp::SimpleTextProperty::Factory(
        my_agent->id(),
        xsd::LangString("en", "MyProperty-Label"),
        xsd::LangString("en", "MyProperty-Description"));
    REQUIRE(static_cast<std::string>(my_property->label().get("en")) == "MyProperty-Label");
    REQUIRE(static_cast<std::string>(my_property->description().get("en")) == "MyProperty-Description");
    REQUIRE(my_property->value_type() == dsp::ValueType::SimpleText);

    SECTION("Subproperties") {
      dsp::PropertyPtr my_subproperty = dsp::SimpleTextProperty::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyProperty-Label"),
          xsd::LangString("en", "MyProperty-Description"),
          my_property->id());
      REQUIRE(my_subproperty->sub_property_of_id() == my_property->id());
      REQUIRE_THROWS_AS(dsp::DateProperty::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyDateSub-Label"),
          xsd::LangString("en", "MyDateSub-Description"),
          my_property->id()), dsp::Error);
    }

    SECTION("SimpleTextProperty") {
      dsp::SimpleTextPropertyPtr my_property1 = dsp::SimpleTextProperty::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyProperty-Label"),
          xsd::LangString("en", "MyProperty-Description"));
      REQUIRE(my_property1->value_type() == dsp::ValueType::SimpleText);
      nlohmann::json json_obj = my_property1->to_json();
      dsp::ModelItem::delete_item<dsp::Property>(my_property1);
      dsp::SimpleTextPropertyPtr same_property = dsp::SimpleTextProperty::Factory(json_obj);
      REQUIRE(same_property->value_type() == dsp::ValueType::SimpleText);
    }

    SECTION("MarkupTextProperty") {
      dsp::MarkupTextPropertyPtr my_property2 = dsp::MarkupTextProperty::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyMarkupText-Label"),
          xsd::LangString("en", "MyMarkupText-Description"));
      REQUIRE(my_property2->value_type() == dsp::ValueType::MarkupText);
      nlohmann::json json_obj = my_property2->to_json();
      dsp::ModelItem::delete_item<dsp::Property>(my_property2);
      dsp::MarkupTextPropertyPtr same_property = dsp::MarkupTextProperty::Factory(json_obj);
      REQUIRE(same_property->value_type() == dsp::ValueType::MarkupText);
    }

    SECTION("BitstreamProperty") {
      dsp::BitstreamPropertyPtr my_property3 = dsp::BitstreamProperty::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyBitstream-Label"),
          xsd::LangString("en", "MyBitstream-Description"));
      REQUIRE(my_property3->value_type() == dsp::ValueType::Bitstream);
      nlohmann::json json_obj = my_property3->to_json();
      dsp::ModelItem::delete_item<dsp::Property>(my_property3);
      dsp::BitstreamPropertyPtr same_property = dsp::BitstreamProperty::Factory(json_obj);
      REQUIRE(same_property->value_type() == dsp::ValueType::Bitstream);
    }

    SECTION("DateProperty") {
      dsp::DatePropertyPtr my_property4 = dsp::DateProperty::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyDate-Label"),
          xsd::LangString("en", "MyDate-Description"));
      REQUIRE(my_property4->value_type() == dsp::ValueType::Date);
      nlohmann::json json_obj = my_property4->to_json();
      dsp::ModelItem::delete_item<dsp::Property>(my_property4);
      dsp::DatePropertyPtr same_property = dsp::DateProperty::Factory(json_obj);
      REQUIRE(same_property->value_type() == dsp::ValueType::Date);
    }

    SECTION("IntegerProeprty") {
      dsp::IntegerPropertyPtr my_property5 = dsp::IntegerProperty::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyInteger-Label"),
          xsd::LangString("en", "MyInteger-Description"));
      REQUIRE(my_property5->value_type() == dsp::ValueType::Integer);
      nlohmann::json json_obj = my_property5->to_json();
      dsp::ModelItem::delete_item<dsp::Property>(my_property5);
      dsp::IntegerPropertyPtr same_property = dsp::IntegerProperty::Factory(json_obj);
      REQUIRE(same_property->value_type() == dsp::ValueType::Integer);
    }

    SECTION("DecimalProperty") {
      dsp::DecimalPropertyPtr my_property6 = dsp::DecimalProperty::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyDecimal-Label"),
          xsd::LangString("en", "MyDecimal-Description"));
      REQUIRE(my_property6->value_type() == dsp::ValueType::Decimal);
      nlohmann::json json_obj = my_property6->to_json();
      dsp::ModelItem::delete_item<dsp::Property>(my_property6);
      dsp::DecimalPropertyPtr same_property = dsp::DecimalProperty::Factory(json_obj);
      REQUIRE(same_property->value_type() == dsp::ValueType::Decimal);
    }

    SECTION("BooleanProperty") {
      dsp::BooleanPropertyPtr my_property7 = dsp::BooleanProperty::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyBoolean-Label"),
          xsd::LangString("en", "MyBoolean-Description"));
      REQUIRE(my_property7->value_type() == dsp::ValueType::Boolean);
      nlohmann::json json_obj = my_property7->to_json();
      dsp::ModelItem::delete_item<dsp::Property>(my_property7);
      dsp::BooleanPropertyPtr same_property = dsp::BooleanProperty::Factory(json_obj);
      REQUIRE(same_property->value_type() == dsp::ValueType::Boolean);
    }

    SECTION("ColorProperty") {
      dsp::ColorPropertyPtr my_property8 = dsp::ColorProperty::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyColor-Label"),
          xsd::LangString("en", "MyColor-Description"));
      REQUIRE(my_property8->value_type() == dsp::ValueType::Color);
      nlohmann::json json_obj = my_property8->to_json();
      dsp::ModelItem::delete_item<dsp::Property>(my_property8);
      dsp::ColorPropertyPtr same_property = dsp::ColorProperty::Factory(json_obj);
      REQUIRE(same_property->value_type() == dsp::ValueType::Color);
    }

    SECTION("GeometryProperty") {
      dsp::GeometryPropertyPtr my_property9 = dsp::GeometryProperty::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyGeometry-Label"),
          xsd::LangString("en", "MyGeometry-Description"));
      REQUIRE(my_property9->value_type() == dsp::ValueType::Geometry);
      nlohmann::json json_obj = my_property9->to_json();
      dsp::ModelItem::delete_item<dsp::Property>(my_property9);
      dsp::GeometryPropertyPtr same_property = dsp::GeometryProperty::Factory(json_obj);
      REQUIRE(same_property->value_type() == dsp::ValueType::Geometry);
    }

    SECTION("Geonameproperty") {
      dsp::GeonamePropertyPtr my_property10 = dsp::GeonameProperty::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyGeoname-Label"),
          xsd::LangString("en", "MyGeoname-Description"));
      REQUIRE(my_property10->value_type() == dsp::ValueType::Geoname);
      nlohmann::json json_obj = my_property10->to_json();
      dsp::ModelItem::delete_item<dsp::Property>(my_property10);
      dsp::GeonamePropertyPtr same_property = dsp::GeonameProperty::Factory(json_obj);
      REQUIRE(same_property->value_type() == dsp::ValueType::Geoname);
    }

    SECTION("IconClassProperty") {
      dsp::IconClassPropertyPtr my_property11 = dsp::IconClassProperty::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyIconClass-Label"),
          xsd::LangString("en", "MyIconClass-Description"));
      REQUIRE(my_property11->value_type() == dsp::ValueType::IconClass);
      nlohmann::json json_obj = my_property11->to_json();
      dsp::ModelItem::delete_item<dsp::Property>(my_property11);
      dsp::IconClassPropertyPtr same_property = dsp::IconClassProperty::Factory(json_obj);
      REQUIRE(same_property->value_type() == dsp::ValueType::IconClass);
    }

    SECTION("UriProperty") {
      dsp::UriPropertyPtr my_property12 = dsp::UriProperty::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyUri-Label"),
          xsd::LangString("en", "MyUri-Description"));
      REQUIRE(my_property12->value_type() == dsp::ValueType::Uri);
      nlohmann::json json_obj = my_property12->to_json();
      dsp::ModelItem::delete_item<dsp::Property>(my_property12);
      dsp::UriPropertyPtr same_property = dsp::UriProperty::Factory(json_obj);
      REQUIRE(same_property->value_type() == dsp::ValueType::Uri);
    }

    SECTION("IntervalProperty") {
      dsp::IntervalPropertyPtr my_property13 = dsp::IntervalProperty::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyInterval-Label"),
          xsd::LangString("en", "MyInterval-Description"));
      REQUIRE(my_property13->value_type() == dsp::ValueType::Interval);
      nlohmann::json json_obj = my_property13->to_json();
      dsp::ModelItem::delete_item<dsp::Property>(my_property13);
      dsp::IntervalPropertyPtr same_property = dsp::IntervalProperty::Factory(json_obj);
      REQUIRE(same_property->value_type() == dsp::ValueType::Interval);
    }

    SECTION("LinkProperty") {
      dsp::ResourceClassPtr my_resclass = dsp::ResourceClass::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyResclass-Label"),
          xsd::LangString("en", "MyResclass-Desscription"));

      dsp::PropertyPtr my_property14 = dsp::LinkProperty::Factory(
          my_agent->id(),
          xsd::LangString("en", "MyInterval-Label"),
          xsd::LangString("en", "MyInterval-Description"),
          my_resclass->id());
      REQUIRE(my_property14->value_type() == dsp::ValueType::Link);
      dsp::LinkPropertyPtr link_property_ptr = std::dynamic_pointer_cast<dsp::LinkProperty>(my_property14);
      REQUIRE(link_property_ptr != nullptr);
      REQUIRE(link_property_ptr->to_resource_class_id() == my_resclass->id());
      nlohmann::json test_obj = my_property14->to_json();
      dsp::ModelItem::delete_item<dsp::LinkProperty>(my_property14);
      dsp::LinkPropertyPtr same_link_property = dsp::LinkProperty::Factory(test_obj);
      REQUIRE(same_link_property->value_type() == dsp::ValueType::Link);
      REQUIRE(same_link_property->to_resource_class_id() == my_resclass->id());
    }
  }

  SECTION("Property JSON tests") {
    dsp::PropertyPtr my_property = dsp::SimpleTextProperty::Factory(
        my_agent->id(),
        xsd::LangString("en", "MyProperty-Label"),
        xsd::LangString("en", "MyProperty-Description"));
    dsp::PropertyPtr my_subproperty = dsp::SimpleTextProperty::Factory(
        my_agent->id(),
        xsd::LangString("en", "MyProperty-Label"),
        xsd::LangString("en", "MyProperty-Description"),
        my_property->id());
    nlohmann::json json_obj = my_subproperty->to_json();
    REQUIRE(json_obj["version"].get<int>() == 1);
    REQUIRE(json_obj["type"].get<std::string>() == "SimpleTextProperty"s);
    REQUIRE(json_obj["sub_property_of"].get<std::string>() == my_property->id().to_string());

    //dsp::SimpleTextPropertyPtr st = dynamic_cast<SimpleTextProperty>(my_subproperty);

    dsp::Identifier id(my_subproperty->id());
    dsp::ValueType value_type(my_subproperty->value_type());
    dsp::Identifier subproperty_of(my_subproperty->sub_property_of_id());
    dsp::ModelItem::delete_item<dsp::Property>(my_subproperty);
    my_subproperty = dsp::SimpleTextProperty::Factory(json_obj);
    REQUIRE(id == my_subproperty->id());
    REQUIRE(value_type == my_subproperty->value_type());
    REQUIRE(subproperty_of == my_subproperty->sub_property_of_id());
  }

}
