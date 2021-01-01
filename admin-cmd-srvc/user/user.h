//
// Created by Ivan Subotic on 27/11/2020.
//

#ifndef SKUNKWORKS_ENTITIES_ADMIN_USER_USER_H_
#define SKUNKWORKS_ENTITIES_ADMIN_USER_USER_H_

#include <memory>
#include <string>

#include "shared/dsp_types/identifier.h"
#include "shared/dsp_types/username.h"
#include "shared/dsp_types/email.h"
#include "shared/dsp_types/password.h"
#include "shared/dsp_types/token.h"
#include "shared/dsp_types/given_name.h"
#include "shared/dsp_types/family_name.h"
#include "shared/dsp_types/status.h"
#include "shared/dsp_types/lang.h"

namespace admin::user {

/*!
 * The class represents a user in the system.
 */
class User {
 public:
  /*!
   * Default constructor, creating an empty user.
   */
  User();

  /*!
   * Constructor for creating a fully populated user.
   */
  User(const std::shared_ptr<dsp::Username> &username,
       const std::shared_ptr<dsp::Email> &email,
       const std::shared_ptr<dsp::Password> &password,
       const std::shared_ptr<dsp::Token> &token,
       const std::shared_ptr<dsp::GivenName> &given_name,
       const std::shared_ptr<dsp::FamilyName> &family_name,
       const std::shared_ptr<dsp::Status> &status,
       const std::shared_ptr<dsp::Lang> &lang);

  inline std::string id() { return id_->value(); };
  inline std::string username() { return username_->value(); };
  inline std::string email() { return email_->value(); };
  inline std::string password() { return password_->value(); };
  inline std::string token() { return token_->value(); };
  inline std::string given_name() { return given_name_->value(); };
  inline std::string family_name() { return family_name_->value(); };
  inline bool status() { return status_->value(); };
  inline std::string lang() { return lang_->value(); };

 private:
  std::shared_ptr<dsp::Identifier> id_;
  std::shared_ptr<dsp::Username> username_;
  std::shared_ptr<dsp::Email> email_;
  std::shared_ptr<dsp::Password> password_;
  std::shared_ptr<dsp::Token> token_;
  std::shared_ptr<dsp::GivenName> given_name_;
  std::shared_ptr<dsp::FamilyName> family_name_;
  std::shared_ptr<dsp::Status> status_;
  std::shared_ptr<dsp::Lang> lang_;
};

} // namespace admin::user

#endif //SKUNKWORKS_ENTITIES_ADMIN_USER_USER_H_
