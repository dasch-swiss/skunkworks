// Created by Lukas Rosenthaler on 25.11.20.


#ifndef SKUNKWORKS_PROPERTY_H
#define SKUNKWORKS_PROPERTY_H

#include <string>
#include <memory>

#include "subject.h"
#include "class_obj.h"
//#include "resource_class.h"

namespace dsp {

enum class ValueType {
  Unknown,
  SimpleText,
  MarkupText,
  Bitstream,
  Date,
  Integer,
  Decimal,
  Color,
  Geometry,
  Geoname,
  IconClass,
  Uri,
  Interval,
  List,
  Link,
};

NLOHMANN_JSON_SERIALIZE_ENUM(ValueType, {
  {ValueType::Unknown, "Unknown"},
  {ValueType::SimpleText, "SimpleText"},
  {ValueType::MarkupText, "MarkupText"},
  {ValueType::Bitstream, "Bitstream"},
  {ValueType::Date, "Date"},
  {ValueType::Integer, "Integer"},
  {ValueType::Decimal, "Decimal"},
  {ValueType::Color, "Color"},
  {ValueType::Geometry, "Geometry"},
  {ValueType::Geoname, "Geoname"},
  {ValueType::IconClass, "IconClass"},
  {ValueType::Uri, "Uri"},
  {ValueType::Interval, "Interval"},
  {ValueType::List, "List"},
  {ValueType::Link, "Link"}
})

class DataModel;

class Property : public ClassObj {
 public:

  static std::shared_ptr<Property> Factory(
      const dsp::Identifier& created_by,
      const xsd::LangString &label,
      const xsd::LangString &description,
      ValueType value_type,
      const dsp::Identifier& sub_property_of = dsp::Identifier::empty_identifier(),
      std::shared_ptr<Observer> obs = {});

  static std::shared_ptr<Property> Factory(const nlohmann::json& json_obj, std::shared_ptr<Observer> obs = {});

  inline ~Property() override {  }

  bool operator==(const Property& other);

  nlohmann::json to_json() override ;

  inline ValueType value_type() { return value_type_; }

  inline dsp::Identifier sub_property_of_id() { return sub_property_of_; }

  inline std::shared_ptr<Property> sub_property_of() { return get_item<Property>(sub_property_of_); }

  friend DataModel;

  inline friend std::ostream &operator<<(std::ostream &out_stream, std::shared_ptr<Property> property_ptr) {
    out_stream << std::setw(4) << property_ptr->to_json();
    return out_stream;
  }

 private:
  Property(
      const dsp::Identifier& created_by,
      const xsd::LangString &label,
      const xsd::LangString &description,
      ValueType value_type,
      const dsp::Identifier& sub_property_of = dsp::Identifier::empty_identifier());

  explicit Property(const nlohmann::json& json_obj);

  ValueType value_type_;
  dsp::Identifier sub_property_of_;

};

using PropertyPtr = std::shared_ptr<Property>;
}

#endif //SKUNKWORKS_PROPERTY_H
