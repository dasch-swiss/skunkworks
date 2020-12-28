//
// Created by Lukas Rosenthaler on 25.11.20.
//

#include <string>

#include "helpers/uuid.h"

#include "property.h"

static const char __file__[] = __FILE__;


namespace dsp {

class ResourceClass;

Property::Property(std::shared_ptr<DataModel> in_data_model,
                   std::shared_ptr<Agent> agent,
                   const xsd::LangString &class_label,
                   const xsd::LangString &class_description,
                   ValueType value_type,
                   const std::shared_ptr<Property>& sub_property_of) :
                   ClassObj(in_data_model, agent, class_label, class_description),
    value_type_(value_type),
    sub_property_of_(sub_property_of) { }

}
