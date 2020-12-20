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


namespace dsp {

class Property; // forward declaration

class ResourceClass {

  typedef struct has_property {
    std::shared_ptr<Property> property_;
    int min_count_;
    int max_count_;
  } HasProperty;

 private:
  xsd::AnyUri id_;
  xsd::String class_label_;
  xsd::String class_description_;
  std::shared_ptr<ResourceClass> sub_class_of_;
  std::unordered_map<std::string, HasProperty> has_properties_;

 public:
  /*!
   *
   * @param class_label
   * @param class_description
   * @param sub_class_of
   */
  ResourceClass(const xsd::String class_label,
                const xsd::String class_description,
                const std::shared_ptr<ResourceClass> sub_class_of);

  inline xsd::AnyUri id() { return id_; }

  inline std::string class_label() { return class_label_; }

  inline std::string class_description() { return class_description_; }

  void add_property(const std::shared_ptr<Property> property, int min_count, int max_count);

  // usage: cout << resource_class_instance << ...;
  inline friend std::ostream &operator<<(std::ostream &outStream, const ResourceClass &rhs) {
    outStream << "ResourceClass:: " << std::endl <<
              "id=" << rhs.id_ << std::endl <<
              "class_label=" << rhs.class_label_ << std::endl;
    return outStream;
  }

};

}

#endif //SKUNKWORKS_RESOURCE_CLASS_H
