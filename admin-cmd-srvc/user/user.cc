//
// Created by Ivan Subotic on 27/11/2020.
//

#include "helpers/uuid.h"
#include "helpers/error.h"
#include "user.h"
#include "value_types/identifier.h"
#include "value_types/username.h"
#include "value_types/email.h"
#include "value_types/password.h"
#include "value_types/token.h"
#include "value_types/given_name.h"
#include "value_types/family_name.h"
#include "value_types/status.h"
#include "value_types/lang.h"

#include <utility>
#include <memory>

namespace admin::user {

User::User(){}

User::User(
    const std::shared_ptr<Username> &username,
    const std::shared_ptr<Email> &email,
    const std::shared_ptr<Password> &password,
    const std::shared_ptr<Token> &token,
    const std::shared_ptr<GivenName> &given_name,
    const std::shared_ptr<FamilyName> &family_name,
    const std::shared_ptr<Status> &status,
    const std::shared_ptr<Lang> &lang) {

  id_ = Identifier();

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
