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
#include "agent.h"

namespace dsp {

class Domain;

class Project : public ModelItem {
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
      const dsp::Shortname &shortname);

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
      const xsd::String &shortname);

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
      const std::string &shortname);

  /*!
   * Factory for managed project
   * @param json_obj
   * @return
   */
  static std::shared_ptr<Project> Factory(const nlohmann::json& json_obj);

  virtual ~Project();

  std::shared_ptr<Project> get(const dsp::Identifier& id);


  inline xsd::DateTimeStamp creation_date() const { return creation_date_; }
  std::shared_ptr<Agent> created_by() const { return get_item<Agent>(created_by_); }
  inline xsd::DateTimeStamp last_modification_date() const { return last_modification_date_; }
  inline std::shared_ptr<Agent> modified_by() const { return get_item<Agent>(modified_by_); }

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
   * Add a new data model to the project.
   *
   * @param data_model
   */
  void add_data_model(const dsp::Identifier &data_model_id);

  /*!
   * Get a data model from the given data model ID
   *
   * @param data_model_id
   * @return
   */
  std::optional<DataModelPtr> get_data_model(const dsp::Identifier &data_model_id);

  /*!
   * Remove the data model from the project.
   * @param data_model_id
   * @return
   */
  std::optional<DataModelPtr> remove_data_model(const dsp::Identifier &data_model_id);

  nlohmann::json to_json();

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
