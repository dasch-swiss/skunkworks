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

  static std::shared_ptr<DataModel> Factory(
      const dsp::Identifier &created_by,
      const dsp::Shortname& shortname,
      std::shared_ptr<Observer> obs = {});

  static std::shared_ptr<DataModel> Factory(const nlohmann::json& json_obj,
                                            std::shared_ptr<Observer> obs = {});

  ~DataModel() override {  }


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
   * Add a resource class to the data model
   *
   * @param resource_class
   */
  void add_resource_class(const Identifier &resource_class);

  /*!
   * Get resource class by ID.
   *
   * @param resource_class_id
   * @return Optional shared_ptr to ResourceClass instance
   */
  std::optional<ResourceClassPtr> get_resource_class(const dsp::Identifier &resource_class_id) const ;

  /*!
   * Remove a resource class from the data model
   *
   * @param resource_class_id
   * @return Optional shared_ptr to ResourceClass instance that has been removed.
   */
  std::optional<ResourceClassPtr> remove_resource_class(const dsp::Identifier &resource_class_id);

  std::unordered_set<dsp::Identifier> get_resource_class_ids() { return resource_classes_; }

  /*!
   * Add a property to the data model
   *
   * @param property
   */
  void add_property(const dsp::Identifier& property);

  /*!
   * Get a property by ID
   *
   * @param property_id
   * @return
   */
  std::optional<PropertyPtr> get_property(const dsp::Identifier &property_id) const ;

  /*!
   * Remove property from data model
   *
   * @param property_id
   * @return Optional shared_ptr to Property instance that has been removed
   */
  std::optional<PropertyPtr> remove_property(const dsp::Identifier &property_id);

  std::unordered_set<dsp::Identifier> get_property_ids() { return properties_; }


  friend Project; // grant access to class Project to private member variable project_

  nlohmann::json to_json() override;

  inline friend std::ostream &operator<<(std::ostream &out_stream, std::shared_ptr<DataModel> data_model_ptr) {
    out_stream << std::setw(4) << data_model_ptr->to_json();
    return out_stream;
  }

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
