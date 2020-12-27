//
// Created by Lukas Rosenthaler on 21.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_CLASS_OBJ_H_
#define SKUNKWORKS_ENTITIES_CLASS_OBJ_H_

#include <set>
#include <memory>

#include "helpers/xsd_types/xsd.h"
#include "configuration.h"
#include "agent.h"
//#include "data_model.h"

namespace dsp {

class DataModel;

class ClassObj {
  /*!
   * Base class for ResourceClass and Property
   */
 public:
  /*!
   * Default constructor
   */
  ClassObj() { configuration_ = Configuration::init(); }

  /*!
   * Constructor taking all necessary parameters
   *
   * @param in_data_model
   * @param agent
   * @param class_label
   * @param class_description
   */
  ClassObj(
      const std::shared_ptr<DataModel>& in_data_model,
      const std::shared_ptr<Agent>& agent,
      const xsd::LangString& class_label,
      const xsd::LangString& class_description
  );

  /*!
   * Constructor with just a ID as parameter
   *
   * @param id
   */
  ClassObj(const xsd::AnyUri &id);

  /*!
   * Getter for ID
   *
   * @return
   */
  [[gnu::pure]] [[nodiscard]]
  inline xsd::AnyUri id() const { return id_; }

  /*!
   * Getter for in_data_model
   * @return
   */

  [[gnu::pure]] [[nodiscard]]
  inline std::shared_ptr<DataModel> in_data_model() const { return in_data_model_.lock(); };

  /*!
   * Getter for creation_date
   *
   * @return
   */
  [[gnu::pure]] [[nodiscard]]
  inline xsd::DateTimeStamp creation_date() const { return creation_date_; }

  /*!
   * Getter for creator
   *
   * @return
   */
  [[gnu::pure]] [[nodiscard]]
  inline std::shared_ptr<Agent> created_by() const { return created_by_.lock(); }

  /*!
   * Getter for lastmodification date
   *
   * @return
   */
  [[gnu::pure]] [[nodiscard]]
  inline xsd::DateTimeStamp last_modification_date() const { return last_modification_date_; }

  /*!
   * Getter for modified_by
   *
   * @return
   */
  [[gnu::pure]] [[nodiscard]]
  inline std::shared_ptr<Agent> modified_by() const { return modified_by_.lock(); }

  /*!
   * Getter for label
   * @return
   */
  [[gnu::pure]] [[nodiscard]]
  inline xsd::LangString class_label() const { return class_label_; }

  /*!
   * Getter for description
   *
   * @return
   */
  [[gnu::pure]] [[nodiscard]]
  inline xsd::LangString class_description() const { return class_description_; }

  /*!
   * Getter for changed set
   * @return
   */
  [[gnu::pure]] [[nodiscard]]
  inline std::set<std::string> changed() const { return changed_; }

  void class_label(const xsd::LangString &class_label);
  void class_description(const xsd::LangString &class_description);

 protected:
  xsd::AnyUri id_;
  std::weak_ptr<DataModel> in_data_model_;
  xsd::DateTimeStamp creation_date_;
  std::weak_ptr<Agent> created_by_;
  xsd::DateTimeStamp last_modification_date_;
  std::weak_ptr<Agent> modified_by_;
  xsd::LangString class_label_;
  xsd::LangString class_description_;
  Configuration *configuration_;
  std::set<std::string> changed_;

  //inline void data_model_id(const std::shared_ptr<DataModel> &in_data_model) { in_data_model_ = in_data_model; }

};


}

#endif //SKUNKWORKS_ENTITIES_CLASS_OBJ_H_
