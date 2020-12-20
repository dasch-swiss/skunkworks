//
// Created by Lukas Rosenthaler on 25.11.20.
//

#ifndef SKUNKWORKS_VALUE_CLASS_H
#define SKUNKWORKS_VALUE_CLASS_H

#include <string>
#include "helpers/xsd_types/xsd.h"

namespace entities {

class ValueClass {
 public:
  ValueClass(const xsd::String &class_label,
             const xsd::String &class_description);
  inline std::string id() { return id_; }

 private:
  std::string id_;
  std::string class_label_;
  std::string class_description_;
};
}

#endif //SKUNKWORKS_VALUE_CLASS_H
