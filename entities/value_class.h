//
// Created by Lukas Rosenthaler on 25.11.20.
//

#ifndef SKUNKWORKS_VALUE_CLASS_H
#define SKUNKWORKS_VALUE_CLASS_H

#include <string>
#include "helpers/xsd_types/xsd.h"

namespace dsp {

class ValueClass {
 private:
  xsd::AnyUri id_;
  xsd::String class_label_;
  xsd::String class_description_;
 public:
  ValueClass(const xsd::String &class_label, const xsd::String &class_description);

  inline xsd::AnyUri id() { return id_; }

};
}

#endif //SKUNKWORKS_VALUE_CLASS_H
