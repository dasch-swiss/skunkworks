//
// Created by Ivan Subotic on 27/11/2020.
//

#include "shared/uuid.h"
#include "shared/error/error.h"
#include "user.h"
#include "shared/dsp_types/identifier.h"
#include "shared/dsp_types/username.h"
#include "shared/dsp_types/email.h"
#include "shared/dsp_types/password.h"
#include "shared/dsp_types/token.h"
#include "shared/dsp_types/given_name.h"
#include "shared/dsp_types/family_name.h"
#include "shared/dsp_types/status.h"
#include "shared/dsp_types/lang.h"

#include <utility>
#include <memory>

namespace admin::user {

User::User(){}

User::User(
    const std::shared_ptr<dsp::Username> &username,
    const std::shared_ptr<dsp::Email> &email,
    const std::shared_ptr<dsp::Password> &password,
    const std::shared_ptr<dsp::Token> &token,
    const std::shared_ptr<dsp::GivenName> &given_name,
    const std::shared_ptr<dsp::FamilyName> &family_name,
    const std::shared_ptr<dsp::Status> &status,
    const std::shared_ptr<dsp::Lang> &lang) {

  id_ = std::make_shared<dsp::Identifier>();

  username_ = username;
  email_ = email;
  password_ = password;
  token_ = token;
  given_name_ = given_name;
  family_name_ = family_name;
  status_ = status;
  lang_ = lang;
}

} // namespace entities::user
