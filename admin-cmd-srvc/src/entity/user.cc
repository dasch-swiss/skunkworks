//
// Created by Ivan Subotic on 27/11/2020.
//

#include "user.h"
#include "shared/dsp_types/username.h"
#include "shared/dsp_types/email.h"
#include "shared/dsp_types/password.h"
#include "shared/dsp_types/token.h"
#include "shared/dsp_types/given_name.h"
#include "shared/dsp_types/family_name.h"
#include "shared/dsp_types/status.h"
#include "shared/dsp_types/lang.h"

#include <memory>

namespace admin {

User::User(
    const std::shared_ptr<dsp::Username> &username,
    const std::shared_ptr<dsp::Email> &email,
    const std::shared_ptr<dsp::Password> &password,
    const std::shared_ptr<dsp::Token> &token,
    const std::shared_ptr<dsp::GivenName> &given_name,
    const std::shared_ptr<dsp::FamilyName> &family_name,
    const std::shared_ptr<dsp::Status> &status,
    const std::shared_ptr<dsp::Lang> &lang) {

  id_->with_uuid_v4();

  username_ = username;
  email_ = email;
  password_ = password;
  token_ = token;
  given_name_ = given_name;
  family_name_ = family_name;
  status_ = status;
  lang_ = lang;
}
std::string User::to_string() {

  

  return std::string();
}
User User::from_string(const std::string &value) {
  return User();
}

} // namespace admin
