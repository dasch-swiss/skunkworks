// Created by Lukas Rosenthaler on 25.11.20.


#ifndef SKUNKWORKS_PROPERTY_H
#define SKUNKWORKS_PROPERTY_H

#include <string>

#include "resource_class.h"
#include "values/base_value.h"

namespace dsp {

class Property {
 private:
  std::string id_;
  std::string class_label_;
  std::string class_description_;
  std::shared_ptr<BaseValue> value_class_;
  std::shared_ptr<Property> sub_class_of_;
 public:
  Property(const std::string class_label,
           const std::string class_description,
           const std::shared_ptr<BaseValue> value_class,
           const std::shared_ptr<Property> sub_class_of = nullptr);

  inline std::string id() { return id_; }


};

}

#endif //SKUNKWORKS_PROPERTY_H
