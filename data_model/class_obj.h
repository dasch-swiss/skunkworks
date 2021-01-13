//
// Created by Lukas Rosenthaler on 21.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_CLASS_OBJ_H_
#define SKUNKWORKS_ENTITIES_CLASS_OBJ_H_

#include <set>
#include <memory>

#include "external/nlohmann/json.hpp"

#include "shared/xsd_types/xsd.h"
#include "shared/dsp_types/identifier.h"
#include "agent.h"
//#include "data_model.h"
#include "subject.h"
#include "model_item.h"

namespace dsp {

class DataModel;

class ClassObj: public ModelItem, public Subject {
  /*!
   * Base class for ResourceClass and Property
   */
 public:
  ClassObj() = delete ;

  /*!
   * Constructor taking all necessary parameters
   *
   * @param in_data_model
   * @param agent
   * @param class_label
   * @param class_description
   */
  ClassObj(
      const dsp::Identifier& created_by,
      const dsp::Identifier& in_data_model,
      const xsd::LangString& class_label,
      const xsd::LangString& class_description
  );


  ClassObj(const nlohmann::json &json_obj);

  inline ~ClassObj() { }

  /*!
   * Getter for in_data_model
   * @return
   */
  [[nodiscard]]
  inline dsp::Identifier in_data_model_id() const { return in_data_model_; };

  std::shared_ptr<DataModel> in_data_model() const { return get_item<DataModel>(in_data_model_); }


  /*!
   * Getter for creation_date
   *
   * @return
   */
  [[nodiscard]]
  inline xsd::DateTimeStamp creation_date() const { return creation_date_; }

  /*!
   * Getter for creator
   *
   * @return
   */
  [[nodiscard]]
  inline dsp::Identifier created_by_id() const { return created_by_; }

  /*!
   * Getter for lastmodification date
   *
   * @return
   */
  [[nodiscard]]
  inline xsd::DateTimeStamp last_modification_date() const { return last_modification_date_; }

  /*!
   * Getter for modified_by
   *
   * @return
   */
  [[nodiscard]]
  inline dsp::Identifier modified_by_id() const { return modified_by_; }

  /*!
   * Getter for label
   * @return
   */
  [[nodiscard]]
  inline xsd::LangString label() const { return label_; }

  /*!
   * Getter for description
   *
   * @return
   */
  [[nodiscard]]
  inline xsd::LangString description() const { return description_; }

  void label(const xsd::LangString &label);

  void description(const xsd::LangString &description);

  bool operator==(const ClassObj &other);

  virtual nlohmann::json to_json();

 protected:
  //dsp::Identifier id_;
  xsd::DateTimeStamp creation_date_;
  dsp::Identifier created_by_;
  dsp::Identifier in_data_model_;
  xsd::DateTimeStamp last_modification_date_;
  dsp::Identifier modified_by_;
  xsd::LangString label_;
  xsd::LangString description_;

  //inline void data_model_id(const std::shared_ptr<DataModel> &in_data_model) { in_data_model_ = in_data_model; }

};


}

#endif //SKUNKWORKS_ENTITIES_CLASS_OBJ_H_
