//
// Created by Lukas Rosenthaler on 19.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_ALL_PROPERTIES_H_
#define SKUNKWORKS_DATA_MODEL_ALL_PROPERTIES_H_

#include "property.h"
#include "properties/simple_text_property.h"
#include "properties/markup_text_property.h"
#include "properties/bitstream_property.h"
#include "properties/date_property.h"
#include "properties/integer_property.h"
#include "properties/decimal_property.h"
#include "properties/boolean_property.h"
#include "properties/color_property.h"
#include "properties/geometry_property.h"
#include "properties/geoname_property.h"
#include "properties/icon_class_property.h"
#include "properties/uri_property.h"
#include "properties/interval_property.h"
#include "properties/link_property.h"

namespace dsp {


class ListProperty : public Property {
 public:
  static std::shared_ptr<ListProperty> Factory(
      const dsp::Identifier& created_by,
      const xsd::LangString& label,
      const xsd::LangString& description,
      const dsp::Identifier& to_resclass,
      const dsp::Identifier& sub_property_of = dsp::Identifier::empty_identifier(),
      std::shared_ptr<Observer> obs = {}) {
    std::shared_ptr<ListProperty> tmp(new ListProperty(created_by, label, description, to_resclass, sub_property_of));
    if (obs) tmp->attach(obs);
    tmp->add_item<ListProperty>();
    tmp->notify(ObserverAction::CREATE, tmp);
    return tmp;
  }
 private:
  ListProperty(
      const dsp::Identifier& created_by,
      const xsd::LangString& label,
      const xsd::LangString& description,
      const dsp::Identifier& list,
      const dsp::Identifier& sub_property_of = dsp::Identifier::empty_identifier(),
      std::shared_ptr<Observer> obs = {})
      : Property(created_by, label, description, ValueType::List, sub_property_of), list_(list) {
  }

  Identifier list_;
};

}

#endif //SKUNKWORKS_DATA_MODEL_ALL_PROPERTIES_H_
