//
// Created by Lukas Rosenthaler on 21.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_DATA_MODEL_H_
#define SKUNKWORKS_ENTITIES_DATA_MODEL_H_

#include <string>
#include <unordered_map>

#include "shared/xsd_types/xsd.h"
#include "property.h"
#include "resource_class.h"


namespace dsp {

class Project;

class DataModel : public std::enable_shared_from_this<DataModel>{
 public:
  /*!
   * Default constructor
   */
  DataModel();

  DataModel(const xsd::String &shortname);
  /*!
   * Constructor taking a shortname as parameter
   *
   * @param shortname
   */
  DataModel(const std::string &shortname);

  /*!
   * Getter for ID
   *
   * @return
   */
  inline dsp::Id id() const { return id_; }

  /*!
   * getter for shortname
   * @return
   */
  inline std::string shortname() const { return shortname_; }

  /*!
   * Getter for project (shared_ptr)
   *
   * @return
   */
  inline std::shared_ptr<Project> project() const { return project_.lock(); }

  /*!
   * Add a resource class to the data model
   *
   * @param resource_class
   */
  void add_resource_class(const std::shared_ptr<ResourceClass> &resource_class);

  /*!
   * Get resource class by ID.
   *
   * @param resource_class_id
   * @return Optional shared_ptr to ResourceClass instance
   */
  std::optional<ResourceClassPtr> get_resource_class(const dsp::Id &resource_class_id) const ;

  /*!
   * Remove a resource class from the data model
   *
   * @param resource_class_id
   * @return Optional shared_ptr to ResourceClass instance that has been removed.
   */
  std::optional<ResourceClassPtr> remove_resource_class(const dsp::Id &resource_class_id);

  /*!
   * Add a property to the data model
   *
   * @param property
   */
  void add_property(const std::shared_ptr<Property> &property);

  /*!
   * Get a property by ID
   *
   * @param property_id
   * @return
   */
  std::optional<PropertyPtr> get_property(const dsp::Id &property_id) const ;

  /*!
   * Remove property from data model
   *
   * @param property_id
   * @return Optional shared_ptr to Property instance that has been removed
   */
  std::optional<PropertyPtr> remove_property(const dsp::Id &property_id);

  friend Project; // grant access to class Project to private member variable project_
 private:

  dsp::Id id_;
  xsd::String shortname_;
  std::weak_ptr<Project> project_;
  std::unordered_map<dsp::Id, std::shared_ptr<ResourceClass>> resource_classes_;
  std::unordered_map<dsp::Id, std::shared_ptr<Property>> properties_;

  //inline void project(const std::shared_ptr<Project> &project) { project_.lock() = project; }

};

using DataModelPtr = std::shared_ptr<DataModel>;

}


#endif //SKUNKWORKS_ENTITIES_DATA_MODEL_H_
