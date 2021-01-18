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
#include "subject.h"
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
    inline static const int unlimited = INT_MAX;
  } HasProperty;


  typedef std::unordered_map<dsp::Identifier, HasProperty> HasPropertiesMap;

  static std::shared_ptr<ResourceClass> Factory(const dsp::Identifier &created_by,
                                                const xsd::LangString &class_label,
                                                const xsd::LangString &class_description,
                                                const dsp::Identifier sub_class_of = dsp::Identifier::empty_identifier(),
                                                std::shared_ptr<Observer> obs = {});

  static std::shared_ptr<ResourceClass> Factory(const nlohmann::json& json_obj, std::shared_ptr<Observer> obs = {});

  /*!
   * Destructor removing the instance from the internal list
   */
  inline virtual ~ResourceClass() {  };

  /*!
   * Serialize the resource class as JSON object
   * @return
   */
  nlohmann::json to_json() override;

  inline dsp::Identifier sub_class_of_id() { return sub_class_of_; }

  /*!
   * Add a property to the resource class with cardinality
   * @param property_id
   * @param min_count
   * @param max_count
   * @param agent_id
   */
  void add_property(const dsp::Identifier& property_id, int min_count, int max_count, const dsp::Identifier& agent_id);

  /*!
   * Add a property to the resource class with cardinality
   * @param property
   * @param min_count
   * @param max_count
   * @param agent_id
   */
  inline void add_property(const PropertyPtr& property, int min_count, int max_count, const dsp::Identifier& agent_id) {
    add_property(property->id(), min_count, max_count, agent_id);
  }

  /*!
   * Add a property to the resource class with cardinality
   *
   * @param property_id
   * @param min_count
   * @param max_count
   * @param agent
   */
  inline void add_property(const dsp::Identifier& property_id, int min_count, int max_count, const AgentPtr& agent) {
    add_property(property_id, min_count, max_count, agent->id());
  }

  /*!
   * Add a property to the resource class with cardinality
   * @param property
   * @param min_count
   * @param max_count
   * @param agent
   */
  inline void add_property(const PropertyPtr& property, int min_count, int max_count, const AgentPtr& agent) {
    add_property(property->id(), min_count, max_count, agent->id());
  }

  /*!
   * Modifiy the min_count of this property
   * @param property_id
   * @param min_count
   * @param agent_id
   */
  void change_min_count(const Identifier &property_id, int min_count, const Identifier &agent_id);

  /*!
   * Modifiy the min_count of this property
   * @param property
   * @param min_count
   * @param agent_id
   */
  inline void change_min_count(const PropertyPtr &property, int min_count, const Identifier &agent_id) {
    change_min_count(property->id(), min_count, agent_id);
  }

  /*!
   * Modifiy the min_count of this property
   * @param property_id
   * @param min_count
   * @param agent
   */
  inline void change_min_count(const Identifier &property_id, int min_count, const AgentPtr &agent) {
    change_min_count(property_id, min_count, agent->id());
  }

  /*!
   * Modifiy the min_count of this property
   * @param property
   * @param min_count
   * @param agent
   */
  inline void change_min_count(const PropertyPtr &property, int min_count, const AgentPtr &agent) {
    change_min_count(property->id(), min_count, agent->id());
  }

  /*!
   * Modifiy the max_count of this property
   * @param property_id
   * @param max_count
   * @param agent_id
   */
  void change_max_count(const Identifier &property_id, int max_count, const Identifier &agent_id);

  /*!
   * Modifiy the max_count of this property
   * @param property
   * @param max_count
   * @param agent_id
   */
  inline void change_max_count(const PropertyPtr &property, int max_count, const Identifier &agent_id) {
    change_max_count(property->id(), max_count, agent_id);
  }

  /*!
   * Modifiy the max_count of this property
   * @param property_id
   * @param max_count
   * @param agent
   */
  inline void change_max_count(const Identifier &property_id, int max_count, const AgentPtr &agent) {
    change_max_count(property_id, max_count, agent->id());
  }

  /*!
   * Modifiy the max_count of this property
   * @param property
   * @param max_count
   * @param agent
   */
  inline void change_max_count(const PropertyPtr &property, int max_count, const AgentPtr &agent) {
    change_max_count(property->id(), max_count, agent->id());
  }

  /*!
   * Remove a property from the ResourceClass instance
   * @param property_id
   * @param agent_id
   */
  void remove_property(const Identifier &property_id, const Identifier &agent_id);

  /*!
   * Remove a property from the ResourceClass instance
   * @param property
   * @param agent_id
   */
  inline void remove_property(const PropertyPtr &property, const Identifier &agent_id) {
    remove_property(property->id(), agent_id);
  }

  /*!
   * Remove a property from the ResourceClass instance
   * @param property_id
   * @param agent
   */
  inline void remove_property(const Identifier &property_id, const AgentPtr &agent) {
    remove_property(property_id, agent->id());
  }

  /*!
   * Remove a property from the ResourceClass instance
   * @param property
   * @param agent
   */
  inline void remove_property(const PropertyPtr &property, const AgentPtr &agent) {
    remove_property(property->id(), agent->id());
  }

  inline HasPropertiesMap has_properties() { return has_properties_; }

  inline friend std::ostream &operator<<(std::ostream &out_stream, std::shared_ptr<ResourceClass> resource_class_ptr) {
    out_stream << std::setw(4) << resource_class_ptr->to_json();
    return out_stream;
  }

  inline std::string to_string() override { return "gaga"s; }

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
