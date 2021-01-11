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
#include "shared/dsp_types/identifier.h"
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
    dsp::Identifier property_;
    int min_count_;
    int max_count_;
  } HasProperty;

 private:
  typedef std::unordered_map<dsp::Identifier, HasProperty> HasPropertiesMap;

 public:
  static std::shared_ptr<ResourceClass> Factory(const dsp::Identifier &created_by,
                                                const xsd::LangString &class_label,
                                                const xsd::LangString &class_description,
                                                const dsp::Identifier sub_class_of = dsp::Identifier::empty_identifier());

  static std::shared_ptr<ResourceClass> Factory(const nlohmann::json& json_obj);

  /*!
   * Destructor removing the instance from the internal list
   */
  inline virtual ~ResourceClass() {  };

  /*!
   * Serialize the resource class as JSON object
   * @return
   */
  nlohmann::json to_json();

  /*!
   * Add a property to the resource class with cardinality
   *
   * @param property
   * @param min_count
   * @param max_count
   */
  void add_property(const dsp::Identifier &property_id, int min_count, int max_count);

  /*!
   * Modifiy the min_count of this property
   *
   * @param property_id
   * @param min_count
   */
  void change_min_count(const dsp::Identifier &property_id, int min_count);

  /*!
   * Modifiy the max_count of this property
   *
   * @param property_id
   * @param max_count
   */
  void change_max_count(const dsp::Identifier &property_id, int max_count);

  /*!
   * Remove a property from the ResourceClass instance
   * @param property_id
   */
  void remove_property(const dsp::Identifier &property_id);


  inline friend std::ostream &operator<<(std::ostream &outStream, ResourceClass &rhs) {
    outStream << "ResourceClass:: " << std::endl <<
              "id=" << rhs.id_ << std::endl;
    for (auto &ll: rhs.label_) {
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
  /*!
   * ResourceClass constructor taking several parameters
   *
   * @param created_by
   * @param class_label
   * @param class_description
   * @param sub_class_of
   */
  ResourceClass(
      const dsp::Identifier &created_by,
      const xsd::LangString &class_label,
      const xsd::LangString &class_description,
      const dsp::Identifier sub_class_of = dsp::Identifier::empty_identifier());

  /*!
   * ResourceClass constructor generating an instance from a json object (de-serializing)
   * @param json_obj
   */
  explicit ResourceClass(const nlohmann::json& json_obj);

  HasPropertiesMap has_properties_;
  dsp::Identifier sub_class_of_;

};

using ResourceClassPtr = std::shared_ptr<ResourceClass>;

}

#endif //SKUNKWORKS_RESOURCE_CLASS_H
