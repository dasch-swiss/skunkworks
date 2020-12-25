//
// Created by Ivan Subotic on 25/11/2020.
//

#ifndef SKUNKWORKS_RESOURCE_CLASS_H
#define SKUNKWORKS_RESOURCE_CLASS_H

#include <memory>         // required for shared_ptr under linux
#include <iostream>
#include <string>
#include <unordered_map>

#include "helpers/xsd_types/xsd.h"
#include "configuration.h"
#include "agent.h"
#include "data_model.h"
#include "class_obj.h"

namespace dsp {

class Property; // forward declaration

class ResourceClass : public ClassObj {

  typedef struct has_property {
    std::shared_ptr<Property> property_;
    int min_count_;
    int max_count_;
  } HasProperty;

 public:
  ResourceClass() = default;
  /*!
   *
   * @param class_label
   * @param class_description
   * @param sub_class_of
   */
  ResourceClass(
      std::shared_ptr<DataModel> in_data_model,
      std::shared_ptr<Agent> agent,
      const xsd::LangString &class_label,
      const xsd::LangString &class_description,
      std::shared_ptr<ResourceClass> sub_class_of = nullptr);

  inline std::string prefix() { return configuration_->resclass_prefix(in_data_model_); }

  void add_property(const std::shared_ptr<Property> property, int min_count, int max_count);

  // usage: cout << resource_class_instance << ...;
  inline friend std::ostream &operator<<(std::ostream &outStream, ResourceClass &rhs) {
    outStream << "ResourceClass:: " << std::endl <<
              "id=" << rhs.id_ << std::endl;
    for (auto &ll: rhs.class_label_) {
      outStream << ll.first << ": " << ll.second << std::endl;
    }
    return outStream;
  }

 private:
  std::shared_ptr<ResourceClass> sub_class_of_;
  std::unordered_map<std::string, HasProperty> has_properties_;


};

}

#endif //SKUNKWORKS_RESOURCE_CLASS_H
