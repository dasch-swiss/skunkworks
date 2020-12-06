//
// Created by Ivan Subotic on 27/11/2020.
//

#ifndef SKUNKWORKS_ENTITIES_ADMIN_USER_USER_H_
#define SKUNKWORKS_ENTITIES_ADMIN_USER_USER_H_

#include <string>

#include "entities/user/values/username.h"
#include "entities/values/agent.h"

namespace entities::user {

/*!
 * The class represents a user in the system.
 */
class User {
 public:
  User(std::shared_ptr<Username> username,
       std::string email,
       std::string password,
       std::string token,
       std::string given_name,
       std::string family_name,
       std::string status,
       std::string lang);
  inline xsd::ID id() { return id_; };
  inline std::shared_ptr<Username> username() { return username_; };
  inline xsd::string email() { return email_; };
  inline xsd::string password() { return password_; };
  inline xsd::string token() { return token_; };
  inline xsd::string given_name() { return given_name_; };
  inline xsd::string family_name() { return family_name_; };
  inline xsd::string status() { return status_; };
  inline xsd::string lang() { return lang_; };
 private:
  xsd::ID id_;
  std::shared_ptr<Username> username_;
  std::string email_;
  std::string password_;
  std::string token_;
  std::string given_name_;
  std::string family_name_;
  std::string status_;
  std::string lang_;
};

} // namespace entities::user

#endif //SKUNKWORKS_ENTITIES_ADMIN_USER_USER_H_
