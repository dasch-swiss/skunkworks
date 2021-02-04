//
// Created by Lukas Rosenthaler on 26.11.20.
//

#ifndef SKUNKWORKS_VALUE_H
#define SKUNKWORKS_VALUE_H

#include <memory>
#include <string>

#include "external/nlohmann/json.hpp"

#include "shared/xsd_types/xsd.h"
#include "data_model/agent.h"
#include "data_model/subject.h"

namespace dsp {

class BaseValue : public ModelItem, public Subject {
 public:

  /*!
   * \brief Default constructor
   */
  BaseValue() = delete;


  BaseValue(const dsp::Identifier &created_by);


  inline BaseValue(const xsd::LangString &comment, const dsp::Identifier &created_by) : BaseValue(created_by) {
    comment_ = comment;
  }


  BaseValue(const nlohmann::json& json_obj);


  inline ~BaseValue() {}

  void remove(const dsp::Identifier &deleted_by);

  void remove(const xsd::LangString& delete_comment, const Identifier &deleted_by);

  /*!
 * \brief getter for creation date
 * \return
 */
  inline xsd::DateTimeStamp creation_date() { return creation_date_; }

  inline Identifier created_by() { return created_by_; }

  inline xsd::DateTimeStamp last_modification_date() { return last_modification_date_; }

  inline bool is_modified() { return modified_by_ != Identifier::empty_identifier(); }

  inline Identifier modified_by() {return modified_by_; }

  inline bool is_deleted() { return deleted_by_ != Identifier::empty_identifier(); }

  inline xsd::DateTimeStamp delete_date() { return delete_date_; }

  inline Identifier deleted_by() { return deleted_by_; }

  /*!
   * \brief Getter for Comment
   * \return
   */
  inline xsd::LangString comment() { return comment_; }

  /*!
   * \brief Getter for the comment of a given language. It lang does not exist, the first lang existing will be returned
   * \param lang
   * \return
   */
  inline xsd::String comment(xsd::Language lang) { return comment_.get(lang); }

  inline xsd::String comment(std::string lang) { return comment_.get(lang); }

  void comment(const xsd::LangString &label, const dsp::Identifier& modified_by);

  void comment_add(const xsd::Language& lang, const xsd::String& text, const dsp::Identifier& modified_by);

  inline void comment_add(const std::string& lang, const std::string& text, const dsp::Identifier& modified_by) {
    comment_add(xsd::Language(lang), xsd::String(text), modified_by);
  }

  void comment_remove(const xsd::Language& lang, const dsp::Identifier& modified_by);

  inline void comment_remove(const std::string& lang, const dsp::Identifier& modified_by) {
    comment_remove(xsd::Language(lang), modified_by);
  }


  bool operator==(const BaseValue &other);

  virtual nlohmann::json to_json() override ;

 protected:
  std::string  type_;
  xsd::DateTimeStamp creation_date_;
  dsp::Identifier created_by_;
  xsd::DateTimeStamp last_modification_date_;
  dsp::Identifier modified_by_;
  xsd::DateTimeStamp delete_date_;
  dsp::Identifier deleted_by_;
  xsd::LangString deletion_comment_;
  xsd::LangString comment_;
};

}


#endif //SKUNKWORKS_VALUE_H
