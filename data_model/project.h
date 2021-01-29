//
// Created by Lukas Rosenthaler on 21.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_PROJECT_H_
#define SKUNKWORKS_ENTITIES_PROJECT_H_

#include <string>
#include <unordered_set>

#include "external/nlohmann/json.hpp"

#include "shared/xsd_types/xsd_any_uri.h"
#include "shared/xsd_types/xsd_restriction.h"
#include "shared/xsd_types/xsd_boolean.h"
#include "shared/dsp_types/identifier.h"
#include "shared/dsp_types/shortcode.h"
#include "shared/dsp_types/shortname.h"

//#include "shared/generic_object_description/generic_object_description.h"
#include "external/nlohmann/json.hpp"
#include "model_item.h"
#include "data_model.h"
#include "subject.h"
#include "agent.h"

namespace dsp {

class Domain;

class Project : public ModelItem, public Subject {
  /*!
   * This class represents a project. It's ID is a named UUID composed of "Project" and the shortcode.
   * It must be constructed using one of the Factory methods and cannot be created usinf the constructor
   * (which is private)!
   */
 public:
  /*!
   * Factory for managed Project
   * @param created_by
   * @param shortcode
   * @param shortname
   * @return
   */
  static std::shared_ptr<Project> Factory(
      const dsp::Identifier &created_by,
      const dsp::Shortcode &shortcode,
      const dsp::Shortname &shortname,
      std::shared_ptr<Observer> obs = {});

  /*!
   * Factory for managed Project
   * @param created_by
   * @param shortcode
   * @param shortname
   * @return
   */
  static std::shared_ptr<Project> Factory(
      const dsp::Identifier &created_by,
      const xsd::String &shortcode,
      const xsd::String &shortname,
      std::shared_ptr<Observer> obs = {});

  /*!
   * Factory for managed Project
   * @param created_by
   * @param shortcode
   * @param shortname
   * @return
   */
  static std::shared_ptr<Project> Factory(
      const dsp::Identifier &created_by,
      const std::string &shortcode,
      const std::string &shortname,
      std::shared_ptr<Observer> obs = {});

  /*!
   * Factory for managed project from json data
   * @param json_obj
   * @param obs
   * @return
   */
  static std::shared_ptr<Project> Factory(const nlohmann::json& json_obj,
                                          std::shared_ptr<Observer> obs = {});

  virtual ~Project();

  /*!
   * Getter for creation date
   * @return
   */
  inline xsd::DateTimeStamp creation_date() const { return creation_date_; }

  /*!
   * Getter for created_by ID
   * @return
   */
  inline dsp::Identifier created_by_id() const { return created_by_; }

  /*!
   * Getter for created_by AgentPtr
   * @return
   */
  inline AgentPtr created_by() const { return get_item<Agent>(created_by_); }

  /*!
   * Getter for last_modification_date
   * @return
   */
  inline xsd::DateTimeStamp last_modification_date() const { return last_modification_date_; }

  /*!
   * Getter for modified_by ID
   * @return
   */
  inline dsp::Identifier modified_by_id() const { return modified_by_; }

  /*!
   * Getter for modified_by AgentPtr
   * @return
   */
  inline AgentPtr modified_by() const { return get_item<Agent>(modified_by_); }

  /*!
   * Getter for Shortcode
   *
   * @return
   */
  inline dsp::Shortcode shortcode() { return shortcode_; }

  /*!
   * Getter for shortname
   *
   * @return
   */
  inline dsp::Shortname shortname() const { return shortname_; }

  /*!
   * Add project to data model
   * @param data_model_id data_model ID
   * @param modified_by modified_by ID
   */
  void add_data_model(const dsp::Identifier &data_model_id, const dsp::Identifier& modified_by);

  /*!
   * Add project to data model
   * @param data_model Shared pointer to DataModel
   * @param modified_by modified_by ID
   */
  inline void add_data_model(const DataModelPtr& data_model, const dsp::Identifier& modified_by) {
    add_data_model(data_model->id(), modified_by);
  }

  /*!
   * Add project to data model
   * @param data_model_id data model ID
   * @param modified_by Shared pointer to modified_by Agent
   */
  inline void add_data_model(const dsp::Identifier &data_model_id, const AgentPtr& modified_by) {
    add_data_model(data_model_id, modified_by->id());
  }

  /*!
   * Add project to data model
   * @param data_model Shared pointer to DataModel
   * @param modified_by Shared pointer to Agent
   */
  inline void add_data_model(const DataModelPtr& data_model, const AgentPtr& modified_by) {
    add_data_model(data_model->id(), modified_by->id());
  }

  /*!
   * Get a data model from the given data model ID
   *
   * @param data_model_id
   * @return
   */
  std::optional<DataModelPtr> get_data_model(const dsp::Identifier& data_model_id);

  /*!
   * Remove the data model from the project.
   * @param data_model_id
   * @param modified_by
   * @return
   */
  std::optional<DataModelPtr> remove_data_model(
      const dsp::Identifier& data_model_id,
      const dsp::Identifier& modified_by);

  /*!
   * Remove the data model from the project.
   * @param data_model
   * @param modified_by
   * @return
   */
  inline std::optional<DataModelPtr> remove_data_model(
      const DataModelPtr &data_model,
      const dsp::Identifier& modified_by) {
    return remove_data_model(data_model->id(), modified_by);
  }

  /*!
   * Remove the data model from the project.
   * @param data_model_id
   * @param modified_by
   * @return
   */
  inline std::optional<DataModelPtr> remove_data_model(
      const dsp::Identifier &data_model_id,
      const AgentPtr & modified_by) {
    return remove_data_model(data_model_id, modified_by->id());
  };

  /*!
   * Remove the data model from the project.
   * @param data_model
   * @param modified_by
   * @return
   */
  inline std::optional<DataModelPtr> remove_data_model(
      const DataModelPtr &data_model,
      const AgentPtr & modified_by) {
    return remove_data_model(data_model->id(), modified_by->id());
  }

  /*!
   * Get list of data models as unordered set of ID's
   * @return
   */
  inline std::unordered_set<dsp::Identifier> get_data_model_ids() { return data_models_; }

  /*!
   * Serialize project as JSON
   * @return
   */
  nlohmann::json to_json() override ;

  inline friend std::ostream &operator<<(std::ostream &out_stream, std::shared_ptr<Project> project_ptr) {
    out_stream << std::setw(4) << project_ptr->to_json();
    return out_stream;
  }

  /*!
   * Convert to a string with some human readable information ("shortcode=<code>;shortname=<name>")
   * @return
   */
  inline std::string  to_string() override {
    return "shortcode="s + static_cast<std::string>(shortcode_) + ";shortname=" + static_cast<std::string>(shortname_);
  }

 private:
  /*!
 * Constructor taking an Agent, a Shortcode and Shortname as parameter
 * @param created_by
 * @param shortcode
 * @param shortname
 */
  Project(const dsp::Identifier &created_by,  const dsp::Shortcode &shortcode, const dsp::Shortname &shortname);

  /*!
   * Constructor taking a Shortcode and a shortname as parameter. Assignes a unique ID (based on a uuid).
   *
   * @param shortcode A xsd::String instance
   * @param shortname A xsd::String instance
   */
  Project(const dsp::Identifier &created_by,  const xsd::String &shortcode, const xsd::String &shortname);

  /*!
   * Constructor taking a Shortcode and a shortname as parameter. Assignes a unique ID (based on a uuid).
   *
   * @param shortcode A std::string instance
   * @param shortname A std::string instance
   */
  Project(const dsp::Identifier &created_by, const std::string &shortcode, const std::string &shortname);

  /*!
   * Constructor from JSON
   *
   * May throw dsp::Error
   *
   * @param json_obj
   */
  explicit Project(const nlohmann::json& json_obj);

  xsd::DateTimeStamp creation_date_;
  dsp::Identifier created_by_;
  xsd::DateTimeStamp last_modification_date_;
  dsp::Identifier modified_by_;
  dsp::Shortcode shortcode_;
  dsp::Shortname shortname_;
  std::unordered_set<dsp::Identifier> data_models_;
};

using ProjectPtr = std::shared_ptr<Project>;

}

#endif //SKUNKWORKS_ENTITIES_PROJECT_H_
