//
// Created by Ivan Subotic on 27/11/2020.
//

#ifndef SKUNKWORKS_ENTITIES_ADMIN_USER_USER_H_
#define SKUNKWORKS_ENTITIES_ADMIN_USER_USER_H_

#include <string>

#include "entities/values/agent.h"

namespace dsp {

/*!
 * The class represents a user in the system.
 */
class User : dsp::Agent {
  xsd::ID id_;
  std::string username_;
  std::string email_;
  std::string password_;
  std::string token_;
  std::string given_name;
  std::string family_name;
  std::string status_;
  std::string lang_;
 public:
  User(std::string username,
       std::string email,
       std::string password,
       std::string token,
       std::string given_name,
       std::string family_name,
       std::string status,
       std::string lang);
  inline xsd::string username() { return username_; };
  inline xsd::string email() { return email_; };
};

}

#endif //SKUNKWORKS_ENTITIES_ADMIN_USER_USER_H_
