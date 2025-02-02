//
// Created by Lukas Rosenthaler on 26.11.20.
//

#ifndef SKUNKWORKS_VALUE_H
#define SKUNKWORKS_VALUE_H

#include <memory>
#include <string>

#include "shared/xsd_types/xsd.h"
#include "data_model/agent.h"

namespace dsp {

class BaseValue {
 public:

  inline BaseValue() { modified_ = false; }

  BaseValue(std::shared_ptr<Agent> created_by, const xsd::LangString &comment);

  /**
   * Getter for creation_date
   *
   * @return xsd::DateTimeStamp
   */
  inline xsd::DateTimeStamp creation_date() { return creation_date_; }

  virtual void create() = 0;

  virtual void remove(std::shared_ptr<Agent> deleted_by);

  virtual void remove(std::shared_ptr<Agent> deleted_by, const xsd::LangString &lang_string);

  virtual void remove(std::shared_ptr<Agent> deleted_by, const xsd::Language &language, const xsd::String &text);

  virtual void remove(std::shared_ptr<Agent> deleted_by, const std::string &language, const std::string &text);

  virtual std::string to_string() = 0;

 protected:

 private:
  xsd::AnyUri id_;
  xsd::DateTimeStamp creation_date_;
  std::shared_ptr<Agent> created_by_;
  xsd::Boolean is_deleted_;
  xsd::DateTimeStamp delete_date_;
  std::shared_ptr<Agent> deleted_by_;
  xsd::LangString delete_comment_;
  xsd::LangString comment_;
  bool modified_;
};

}


#endif //SKUNKWORKS_VALUE_H
