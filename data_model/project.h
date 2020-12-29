//
// Created by Lukas Rosenthaler on 21.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_PROJECT_H_
#define SKUNKWORKS_ENTITIES_PROJECT_H_

#include <string>
#include <unordered_map>

#include "shared/xsd_types/xsd_any_uri.h"
#include "shared/xsd_types/xsd_restriction.h"

#include "data_model.h"

namespace dsp {


class Project : public std::enable_shared_from_this<Project> {
 public:
  /*!
   * Default constructor. Assignes a unique ID (based on a uuid) and initializes restrictions for the
   * shortcode and shortname.
   */
  Project();

  /*!
   * Constructor taking a shortcode and a shortname as parameter. Assignes a unique ID (based on a uuid).
   *
   * @param shortcode A xsd::String instance
   * @param shortname A xsd::String instance
   */
  inline Project(const std::shared_ptr<Agent> &created_by,  xsd::String &shortcode, const xsd::String &shortname) : Project() {
    created_by_ = created_by;
    shortcode_ = shortcode;
    shortname_ = shortname;
  }

  /*!
   * Constructor taking a shortcode and a shortname as parameter. Assignes a unique ID (based on a uuid).
   *
   * @param shortcode A std::string instance
   * @param shortname A std::string instance
   */
  inline Project(const std::shared_ptr<Agent> &created_by, const std::string &shortcode, const std::string &shortname) : Project() {
    created_by_ = created_by;
    shortcode_ = shortcode;
    shortname_ = shortname;
  }

  /*!
   * Getter for shortcode
   *
   * @return
   */
  [[gnu::pure]] inline xsd::String shortcode() { return shortcode_; }

  /*!
   * Getter for shortname
   *
   * @return
   */
  [[gnu::pure]] inline xsd::String shortname() const { return shortname_; }

  /*!
   * Getter for the ID
   *
   * @return
   */
  [[gnu::pure]] inline xsd::AnyUri id() const { return id_; }


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
  std::optional<DataModelPtr> get_data_model(const xsd::AnyUri &data_model_id);

  /*!
   * Remove the data model from the project.
   * @param data_model_id
   * @return
   */
  std::optional<DataModelPtr> remove_data_model(const xsd::AnyUri &data_model_id);

 private:
  xsd::AnyUri id_;
  xsd::DateTimeStamp creation_date_;
  std::weak_ptr<Agent> created_by_;
  xsd::DateTimeStamp last_modification_date_;
  std::weak_ptr<Agent> modified_by_;
  xsd::String shortcode_;
  xsd::String shortname_;
  std::unordered_map<xsd::AnyUri, std::shared_ptr<DataModel>> data_models_;
};

using ProjectPtr = std::shared_ptr<Project>;

}


#endif //SKUNKWORKS_ENTITIES_PROJECT_H_
