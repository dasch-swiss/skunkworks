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
  inline Identifier id() { return id_; };
  inline Username username() { return username_; };
  inline Email email() { return email_; };
  inline Password password() { return password_; };
  inline Token token() { return token_; };
  inline GivenName given_name() { return given_name_; };
  inline FamilyName family_name() { return family_name_; };
  inline Status status() { return status_; };
  inline Lang lang() { return lang_; };

 private:
  Identifier id_;
  Username username_;
  Email email_;
  Password password_;
  Token token_;
  GivenName given_name_;
  FamilyName family_name_;
  Status status_;
  Lang lang_;
};

} // namespace admin::user

#endif //SKUNKWORKS_ENTITIES_ADMIN_USER_USER_H_
