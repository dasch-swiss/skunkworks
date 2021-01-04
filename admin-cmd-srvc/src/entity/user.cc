//
// Created by Ivan Subotic on 27/11/2020.
//

#include <memory>
#include "shared/error/error.h"
#include "shared/dsp_types/username.h"
#include "shared/dsp_types/email.h"
#include "shared/dsp_types/password.h"
#include "shared/dsp_types/token.h"
#include "shared/dsp_types/given_name.h"
#include "shared/dsp_types/family_name.h"
#include "shared/dsp_types/status.h"
#include "shared/dsp_types/lang.h"
#include "user.h"

static const char file_[] = __FILE__;

namespace admin {

User::User(
    const dsp::Username &username,
    const dsp::Email &email,
    const dsp::Password &password,
    const dsp::Token &token,
    const dsp::GivenName &given_name,
    const dsp::FamilyName &family_name,
    const dsp::Status &status,
    const dsp::Lang &lang) {

  id_.with_uuid_v4();

  username_ = username;
  email_ = email;
  password_ = password;
  token_ = token;
  given_name_ = given_name;
  family_name_ = family_name;
  status_ = status;
  lang_ = lang;
}

/*!
 * Serialize the user TO JSON.
 */
nlohmann::json User::to_json() const {

  nlohmann::json json_obj = {
      {"class", "admin::User"},
      {"id", id_.value()},
      {"username", username_.value()},
      {"email", email_->value()},
      {"password", password_->value()},
      {"token", token_->value()},
      {"given_name", given_name_->value()},
      {"family_name", family_name_->value()},
      {"status", status_->value()},
      {"lang", lang_->value()}
  };

  return json_obj;
}

/*!
 * Deserialize the user from JSON.
 */
User User::from_json(const nlohmann::json &json_obj) {

  std::shared_ptr<User> user;

  if (json_obj.contains("class") && (json_obj["class"] == "admin::User")) throw dsp::Error(file_, __LINE__, "Deserialization of admin::User failed!");

  if (!json_obj.contains("id")) throw dsp::Error(file_, __LINE__, R"(Json object missing "id".)");
  id_ = dsp::Identifier(json_obj["id"].get<std::string>());

  if (!json_obj.contains("creation_date")) throw Error(file_, __LINE__, R"(Json object missing "creation_date".)");
  project->creation_date_ = xsd::DateTimeStamp(json_obj["creation_date"]);
  if (!json_obj.contains("created_by")) throw Error(file_, __LINE__, R"(Json object missing "created_by")");
  dsp::Identifier created_by_id(json_obj["created_by"]);




  return std::shared_ptr<User>();
}

} // namespace admin
