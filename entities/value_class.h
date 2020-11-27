//
// Created by Lukas Rosenthaler on 25.11.20.
//

#ifndef SKUNKWORKS_VALUE_CLASS_H
#define SKUNKWORKS_VALUE_CLASS_H

#include <string>

namespace dsp {

class ValueClass {
 private:
  std::string id_;
  std::string class_label_;
  std::string class_description_;
 public:
  ValueClass(const std::string class_label, const std::string class_description);
  ValueClass(const char *class_label, const char *class_description);

  inline std::string id() { return id_; }

};
}

#endif //SKUNKWORKS_VALUE_CLASS_H
