//
// Created by Ivan Subotic on 27/11/2020.
//

#include "helpers/uuid.h"
#include "entities/error.h"
#include "user.h"

#include <utility>

namespace entities::user {

User::User(
    std::shared_ptr<Username> username,
    std::string email,
    std::string password,
    std::string token,
    std::string given_name,
    std::string family_name,
    std::string status,
    std::string lang) {

  id_ = uuid::generate_uuid_v4();

  username_ = std::move(username);

  //ToDo: check with regex for validity
  if (email.length() > 0) {
    email_ = std::move(email);
  } else {
    throw entities::Error(__file__, __LINE__, "Email is empty!");
  }

  //ToDo: check with regex for validity
  if (password.length() > 0) {
    password_ = std::move(password);
  } else {
    throw entities::Error(__file__, __LINE__, "Password is empty!");
  }

  //ToDo: check with regex for validity
  if (token.length() > 0) {
    token_ = std::move(token);
  } else {
    throw entities::Error(__file__, __LINE__, "Token is empty!");
  }

  //ToDo: check with regex for validity
  if (given_name.length() > 0) {
    given_name_ = std::move(given_name);
  } else {
    throw entities::Error(__file__, __LINE__, "Given Name is empty!");
  }

  //ToDo: check with regex for validity
  if (family_name.length() > 0) {
    family_name_ = std::move(family_name);
  } else {
    throw entities::Error(__file__, __LINE__, "Family Name is empty!");
  }

  //ToDo: check with regex for validity
  if (status.length() > 0) {
    status_ = std::move(status);
  } else {
    throw entities::Error(__file__, __LINE__, "Status is empty!");
  }

  //ToDo: check with regex for validity
  if (lang.length() > 0) {
    lang_ = std::move(lang);
  } else {
    throw entities::Error(__file__, __LINE__, "Lang is empty!");
  }
}

} // namespace entities::user
