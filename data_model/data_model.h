//
// Created by Lukas Rosenthaler on 21.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_DATA_MODEL_H_
#define SKUNKWORKS_ENTITIES_DATA_MODEL_H_

#include <memory>
#include <string>
#include <unordered_set>

#include "shared/xsd_types/xsd.h"
#include "property.h"
//#include "project.h"
#include "subject.h"
#include "resource_class.h"
#include "model_item.h"


namespace dsp {

class Project;

class DataModel : public ModelItem, public Subject {
 public:

  /*!
   * DataModel factory for managed data model
   * @param created_by
   * @param shortname
   * @param obs [default: empty]
   * @return
   */
  static std::shared_ptr<DataModel> Factory(
      const dsp::Identifier &created_by,
      const dsp::Shortname& shortname,
      std::shared_ptr<Observer> obs = {});

  static std::shared_ptr<DataModel> Factory(const nlohmann::json& json_obj,
                                            std::shared_ptr<Observer> obs = {});

  ~DataModel() override = default;

  inline xsd::DateTimeStamp creation_date() { return creation_date_; }

  inline dsp::Identifier created_by_id() const { return created_by_; }

  inline AgentPtr created_by() const { return ModelItem::get_item<Agent>(created_by_); }

  inline dsp::Identifier modified_by_id() const { return modified_by_; }

  inline AgentPtr modified_by() const { return ModelItem::get_item<Agent>(modified_by_); }

  inline xsd::DateTimeStamp last_modification_date() { return last_modification_date_; }

  /*!
   * getter for shortname
   * @return
   */
  inline dsp::Shortname shortname() const { return shortname_; }

  inline dsp::Identifier project_id() const { return project_; }
  /*!
   * Getter for project (shared_ptr)
   *
   * @return
   */
  std::shared_ptr<Project> project() const ;

  /*!
   * Add resource class to data model
   * @param resource_class_id
   * @param agent_id
   */
  void add_resource_class(const Identifier& resource_class_id, const Identifier& agent_id);

  /*!
   * Add resource class to data model
   * @param resource_class
   * @param agent_id
   */
  inline void add_resource_class(const ResourceClassPtr& resource_class, const Identifier& agent_id) {
    add_resource_class(resource_class->id(), agent_id);
  }

  /*!
   * Add resource class to data model
   * @param resource_class_id
   * @param agent
   */
  inline void add_resource_class(const Identifier& resource_class_id, const AgentPtr& agent) {
    add_resource_class(resource_class_id, agent->id());
  }

  /*!
   * Add resource class to data model
   * @param resource_class
   * @param agent
   */
  inline void add_resource_class(const ResourceClassPtr& resource_class, const AgentPtr& agent) {
    add_resource_class(resource_class->id(), agent->id());
  }

  /*!
   * Get resource class by ID.
   *
   * @param resource_class_id
   * @return Optional shared_ptr to ResourceClass instance
   */
  std::optional<ResourceClassPtr> get_resource_class(const Identifier &resource_class_id) const ;

  /*!
   * Remove a resource class from the data model
   * @param resource_class_id
   * @param agent_id
   * @return
   */
  std::optional<ResourceClassPtr> remove_resource_class(const Identifier &resource_class_id, const Identifier& agent_id);

  /*!
   * Remove a resource class from the data model
   * @param resource_class
   * @param agent_id
   * @return
   */
  inline std::optional<ResourceClassPtr> remove_resource_class(const ResourceClassPtr &resource_class, const Identifier& agent_id) {
    return remove_resource_class(resource_class->id(), agent_id);
  }

  /*!
   * Remove a resource class from the data model
   * @param resource_class_id
   * @param agent
   * @return
   */
  inline std::optional<ResourceClassPtr> remove_resource_class(const Identifier &resource_class_id, const AgentPtr& agent) {
    return remove_resource_class(resource_class_id, agent->id());
  }

  /*!
   * Remove a resource class from the data model
   * @param resource_class
   * @param agent
   * @return
   */
  inline std::optional<ResourceClassPtr> remove_resource_class(const ResourceClassPtr &resource_class, const AgentPtr& agent) {
    return remove_resource_class(resource_class->id(), agent->id());
  }

  std::unordered_set<dsp::Identifier> get_resource_class_ids() { return resource_classes_; }

  /*!
   * Add property to the data model
   * @param property_id
   * @param agent_id
   */
  void add_property(const dsp::Identifier& property_id, const dsp::Identifier& agent_id);

  /*!
   * Add property ti the data model
   * @param property_id
   * @param agent
   */
  inline void add_property(const dsp::Identifier& property_id, AgentPtr agent) {
    add_property(property_id, agent->id());
  }

  /*!
   * Add property to the data model
   * @param property
   * @param agent_id
   */
  inline void add_property(const PropertyPtr property, const dsp::Identifier& agent_id) {
    add_property(property->id(), agent_id);
  }

  /*!
   * Add property to the data model
   * @param property
   * @param agent
   */
  inline void add_property(const PropertyPtr property, AgentPtr agent) {
    add_property(property->id(), agent->id());
  }

  /*!
   * Get a property by ID
   *
   * @param property_id
   * @return
   */
  std::optional<PropertyPtr> get_property(const dsp::Identifier &property_id) const ;

  /*!
   * Remove property from data model
   * @param property_id
   * @param agent_id
   * @return
   */
  std::optional<PropertyPtr> remove_property(const dsp::Identifier &property_id, const dsp::Identifier& agent_id);

  inline std::optional<PropertyPtr> remove_property(const PropertyPtr& property, const dsp::Identifier& agent_id) {
    return remove_property(property->id(), agent_id);
  }

  inline std::optional<PropertyPtr> remove_property(const dsp::Identifier &property_id, const AgentPtr& agent) {
    return remove_property(property_id, agent->id());
  }

  inline std::optional<PropertyPtr> remove_property(const PropertyPtr& property, const AgentPtr & agent) {
    return remove_property(property->id(), agent->id());
  }

  /*!
   * Get all property ids as set
   * @return
   */
  std::unordered_set<dsp::Identifier> get_property_ids() { return properties_; }

  friend Project; // grant access to class Project to private member variable project_

  nlohmann::json to_json() override;

  inline friend std::ostream &operator<<(std::ostream &out_stream, std::shared_ptr<DataModel> data_model_ptr) {
    out_stream << std::setw(4) << data_model_ptr->to_json();
    return out_stream;
  }

  std::string to_string() override { return "gaga"s; }

 private:
  DataModel(const dsp::Identifier &created_by, const dsp::Shortname& shortname);

  explicit DataModel(const nlohmann::json& json_obj);

  xsd::DateTimeStamp creation_date_;
  dsp::Identifier created_by_;
  xsd::DateTimeStamp last_modification_date_;
  dsp::Identifier modified_by_;
  dsp::Shortname shortname_;
  dsp::Identifier project_;
  std::unordered_set<dsp::Identifier> resource_classes_;
  std::unordered_set<dsp::Identifier> properties_;
};

using DataModelPtr = std::shared_ptr<DataModel>;

}


#endif //SKUNKWORKS_ENTITIES_DATA_MODEL_H_
