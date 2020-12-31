//
// Created by Ivan Subotic on 27/11/2020.
//

#ifndef SKUNKWORKS_ENTITIES_ADMIN_USER_USER_H_
#define SKUNKWORKS_ENTITIES_ADMIN_USER_USER_H_

#include <memory>
#include <string>

#include "value_types/identifier.h"
#include "value_types/username.h"
#include "value_types/email.h"
#include "value_types/password.h"
#include "value_types/token.h"
#include "value_types/given_name.h"
#include "value_types/family_name.h"
#include "value_types/status.h"
#include "value_types/lang.h"

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
  User(const std::shared_ptr<Username> &username,
       const std::shared_ptr<Email> &email,
       const std::shared_ptr<Password> &password,
       const std::shared_ptr<Token> &token,
       const std::shared_ptr<GivenName> &given_name,
       const std::shared_ptr<FamilyName> &family_name,
       const std::shared_ptr<Status> &status,
       const std::shared_ptr<Lang> &lang);

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
  std::shared_ptr<Identifier> id_;
  std::shared_ptr<Username> username_;
  std::shared_ptr<Email> email_;
  std::shared_ptr<Password> password_;
  std::shared_ptr<Token> token_;
  std::shared_ptr<GivenName> given_name_;
  std::shared_ptr<FamilyName> family_name_;
  std::shared_ptr<Status> status_;
  std::shared_ptr<Lang> lang_;
};

} // namespace admin::user

#endif //SKUNKWORKS_ENTITIES_ADMIN_USER_USER_H_
