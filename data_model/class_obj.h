//
// Created by Lukas Rosenthaler on 21.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_CLASS_OBJ_H_
#define SKUNKWORKS_ENTITIES_CLASS_OBJ_H_

#include <set>

#include "helpers/xsd_types/xsd.h"
#include "configuration.h"
#include "agent.h"
#include "data_model.h"

namespace dsp {

class ClassObj {
 public:
  ClassObj() { configuration_ = Configuration::init(); }

  ClassObj(
      std::shared_ptr<DataModel> in_data_model,
      std::shared_ptr<Agent> agent,
      xsd::LangString class_label,
      xsd::LangString class_description
  );

  ClassObj(const xsd::AnyUri &id);

  inline xsd::AnyUri id() { return id_; }
  inline std::shared_ptr<DataModel> in_data_model() { return in_data_model_; };
  inline xsd::DateTimeStamp creation_date() { return creation_date_; }
  inline std::shared_ptr<Agent> created_by() { return created_by_; }
  inline xsd::DateTimeStamp last_modification_date() { return last_modification_date_; }
  inline std::shared_ptr<Agent> modified_by() { return modified_by_; }
  inline xsd::LangString class_label() { return class_label_; }
  inline xsd::LangString class_description() { return class_description_; }
  inline std::set<std::string> changed() { return changed_; }

  void class_label(const xsd::LangString &class_label);
  void class_description(const xsd::LangString &class_description);


 protected:
  xsd::AnyUri id_;
  std::shared_ptr<DataModel> in_data_model_;
  xsd::DateTimeStamp creation_date_;
  std::shared_ptr<Agent> created_by_;
  xsd::DateTimeStamp last_modification_date_;
  std::shared_ptr<Agent> modified_by_;
  xsd::LangString class_label_;
  xsd::LangString class_description_;
  Configuration *configuration_;
  std::set<std::string> changed_;
};


}

#endif //SKUNKWORKS_ENTITIES_CLASS_OBJ_H_
