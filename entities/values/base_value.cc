//
// Created by Lukas Rosenthaler on 26.11.20.
//

#include <time.h>
#include "base_value_class.h"
#include "third_party/jansson/jansson.h"

namespace dsp {

Value::Value(std::shared_ptr<Agent> created_by, const xsd::LangString &comment) {
  created_by_ = created_by;
  comment_ = comment;
  modified_ = false;
}

void Value::remove(const std::shared_ptr<Agent> deleted_by) {
  is_deleted_ = true;
  delete_date_ = xsd::DateTimeStamp(); // actual date-time-stamp of now
  deleted_by_ = deleted_by;
}

void Value::remove(std::shared_ptr<Agent> deleted_by, const xsd::LangString &lang_string) {
  remove(deleted_by);
  delete_comment_ = lang_string;
}

void Value::remove(std::shared_ptr<Agent> deleted_by, const xsd::Language &language, const xsd::String &text) {
  remove(deleted_by);
  delete_comment_ = xsd::LangString(language, text);
}

void Value::remove(std::shared_ptr<Agent> deleted_by, const std::string &language, const std::string &text) {
  remove(deleted_by, xsd::LangString(language, text));
}

}