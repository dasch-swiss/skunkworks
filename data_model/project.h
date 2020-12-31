//
// Created by Lukas Rosenthaler on 21.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_PROJECT_H_
#define SKUNKWORKS_ENTITIES_PROJECT_H_

#include <string>
#include <unordered_map>

#include "shared/xsd_types/xsd_any_uri.h"
#include "shared/xsd_types/xsd_restriction.h"
#include "shared/dsp_types/id.h"
#include "shared/dsp_types/shortcode.h"
#include "shared/dsp_types/shortname.h"

#include "data_model.h"

namespace dsp {


class Project : public std::enable_shared_from_this<Project> {
 public:
  /*!
   * Default constructor. Assignes a unique ID (based on a uuid) and initializes restrictions for the
   * Shortcode and shortname.
   */
  Project();

  /*!
   * Constructor taking an Agent, a Shortcode and Shortname as parameter
   * @param created_by
   * @param shortcode
   * @param shortname
   */
  Project(const std::shared_ptr<Agent> &created_by,  dsp::Shortcode &shortcode, const dsp::Shortname &shortname);

  /*!
   * Constructor taking a Shortcode and a shortname as parameter. Assignes a unique ID (based on a uuid).
   *
   * @param shortcode A xsd::String instance
   * @param shortname A xsd::String instance
   */
  Project(const std::shared_ptr<Agent> &created_by,  xsd::String &shortcode, const xsd::String &shortname);

  /*!
   * Constructor taking a Shortcode and a shortname as parameter. Assignes a unique ID (based on a uuid).
   *
   * @param shortcode A std::string instance
   * @param shortname A std::string instance
   */
  Project(const std::shared_ptr<Agent> &created_by, const std::string &shortcode, const std::string &shortname);

  /*!
   * Getter for Shortcode
   *
   * @return
   */
  [[gnu::pure]] inline dsp::Shortcode shortcode() { return shortcode_; }

  /*!
   * Getter for shortname
   *
   * @return
   */
  [[gnu::pure]] inline dsp::Shortname shortname() const { return shortname_; }

  /*!
   * Getter for the ID
   *
   * @return
   */
  [[gnu::pure]] inline dsp::Id id() const { return id_; }


  /*!
   * Add a new data model to the project.
   *
   * @param data_model
   */
  void add_data_model(const std::shared_ptr<DataModel> &data_model);

  /*!
   * Get a data model from the given data model ID
   *
   * @param data_model_id
   * @return
   */
  std::optional<DataModelPtr> get_data_model(const dsp::Id &data_model_id);

  /*!
   * Remove the data model from the project.
   * @param data_model_id
   * @return
   */
  std::optional<DataModelPtr> remove_data_model(const dsp::Id &data_model_id);

 private:
  dsp::Id id_;
  xsd::DateTimeStamp creation_date_;
  std::weak_ptr<Agent> created_by_;
  xsd::DateTimeStamp last_modification_date_;
  std::weak_ptr<Agent> modified_by_;
  dsp::Shortcode shortcode_;
  dsp::Shortname shortname_;
  std::unordered_map<dsp::Id, std::shared_ptr<DataModel>> data_models_;
};

using ProjectPtr = std::shared_ptr<Project>;

}


#endif //SKUNKWORKS_ENTITIES_PROJECT_H_
