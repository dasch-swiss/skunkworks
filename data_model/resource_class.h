//
// Created by Ivan Subotic on 25/11/2020.
//

#ifndef SKUNKWORKS_RESOURCE_CLASS_H
#define SKUNKWORKS_RESOURCE_CLASS_H

#include <memory>         // required for shared_ptr under linux
#include <iostream>
#include <string>
#include <unordered_map>

#include "shared/xsd_types/xsd.h"
#include "configuration.h"
#include "agent.h"
#include "class_obj.h"
#include "property.h"

namespace dsp {


class DataModel;

class ResourceClass : public ClassObj {
  /*!
   * Implements the ResourceClass class.
   *
   * The ResourceClass defines the template for resources. A ResourceClass defines several "properties"
   * that must have a given cardinality. The properties are hold in an unordered_map of HasProperty structs.
   * You can iterate over the ResourceClass to get all HasProperty elements.
   */
 public:
  typedef struct has_property {
    std::weak_ptr<Property> property_;
    int min_count_;
    int max_count_;
  } HasProperty;

 private:
  typedef std::unordered_map<std::string, HasProperty> HasPropertiesMap;

 public:

  /*!
   * Default constructor
   */
  ResourceClass() = default;

  /*!
   * Constructor for ResourceClass. Please note that the resource class should be added to a data model!
   *
   * @param agent
   * @param class_label
   * @param class_description
   * @param sub_class_of
   */
  ResourceClass(
      const std::shared_ptr<Agent> &agent,
      const xsd::LangString &class_label,
      const xsd::LangString &class_description,
      std::shared_ptr<ResourceClass> sub_class_of = nullptr);

  /*!
   * Add a property to the resource class with cardinality
   *
   * @param property
   * @param min_count
   * @param max_count
   */
  void add_property(const std::shared_ptr<Property> &property, int min_count, int max_count);

  /*!
   * Modifiy the min_count of this property
   *
   * @param property_id
   * @param min_count
   */
  void change_min_count(const xsd::String &property_id, int min_count);

  /*!
   * Modifiy the max_count of this property
   *
   * @param property_id
   * @param max_count
   */
  void change_max_count(const xsd::String &property_id, int max_count);

  inline friend std::ostream &operator<<(std::ostream &outStream, ResourceClass &rhs) {
    outStream << "ResourceClass:: " << std::endl <<
              "id=" << rhs.id_ << std::endl;
    for (auto &ll: rhs.class_label_) {
      outStream << ll.first << ": " << ll.second << std::endl;
    }
    return outStream;
  }

  friend DataModel; // allows access to data_model_id(...)

  typedef HasPropertiesMap::iterator iterator;
  typedef HasPropertiesMap::const_iterator const_iterator;
  iterator begin() { return has_properties_.begin(); }
  iterator end() { return has_properties_.end(); }

 private:

  HasPropertiesMap has_properties_;
  std::shared_ptr<ResourceClass> sub_class_of_;

};

using ResourceClassPtr = std::shared_ptr<ResourceClass>;

}

#endif //SKUNKWORKS_RESOURCE_CLASS_H
