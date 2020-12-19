//
// Created by Ivan Subotic on 25/11/2020.
//

#ifndef SKUNKWORKS_RESOURCE_CLASS_H
#define SKUNKWORKS_RESOURCE_CLASS_H

#include <memory>         // required for shared_ptr under linux
#include <iostream>
#include <string>
#include <unordered_map>

#include "property.h"

namespace dsp {

class ResourceClass {

//  struct has_property {
//    std::shared_ptr<Property> property_;
//    int min_count_;
//    int max_count_;
//  } HasProperty;

 private:
  std::string id_;
  std::string class_label_;
  std::string class_description_;
  std::shared_ptr<ResourceClass> sub_class_of_;
  // std::unordered_map<std::string, HasProperty> has_properties_;

 public:
  /*!
   *
   * @param class_label
   * @param class_description
   * @param sub_class_of
   */
  ResourceClass(const std::string class_label,
                const std::string class_description,
                const std::shared_ptr<ResourceClass> sub_class_of);

  inline std::string id() { return id_; }

  inline std::string class_label() { return class_label_; }

  inline std::string class_description() { return class_description_; }

  // void add_property(const std::shared_ptr<Property> property, int min_count, int max_count);

  // usage: cout << resource_class_instance << ...;
//  inline friend std::ostream &operator<<(std::ostream &outStream, const ResourceClass &rhs) {
//    outStream << "ResourceClass:: " << std::endl <<
//              "id=" << rhs.id_ << std::endl <<
//              "class_label=" << rhs.class_label_ << std::endl;
//  }

};

}

#endif //SKUNKWORKS_RESOURCE_CLASS_H
