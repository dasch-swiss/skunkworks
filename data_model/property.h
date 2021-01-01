// Created by Lukas Rosenthaler on 25.11.20.


#ifndef SKUNKWORKS_PROPERTY_H
#define SKUNKWORKS_PROPERTY_H

#include <string>

#include "class_obj.h"
#include "resource_class.h"

namespace dsp {

enum class ValueType {
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

class Property : public ClassObj {
 public:
  inline Property() : ClassObj() {}

  Property(
      std::shared_ptr<DataModel> in_data_model,
      std::shared_ptr<Agent> agent,
      const xsd::LangString &class_label,
      const xsd::LangString &class_description,
      ValueType value_type,
      const std::shared_ptr<Property>& sub_property_of = nullptr);

  ValueType value_type() { return value_type_; }

  const std::shared_ptr<Property> sub_property_of() { return sub_property_of_; }


 private:
  ValueType value_type_;
  std::shared_ptr<Property> sub_property_of_;

};

}

#endif //SKUNKWORKS_PROPERTY_H
