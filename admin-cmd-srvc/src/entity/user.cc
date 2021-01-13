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

/*!
 * Default constructor. Creates an empty user.
 */
User::User() {
  id_ = dsp::Identifier("empty");
}

/*!
 * Construct user from provided values.
 */
User::User(
    const dsp::Username& username,
    const dsp::Email& email,
    const dsp::Password& password,
    const dsp::Token& token,
    const dsp::GivenName& given_name,
    const dsp::FamilyName& family_name,
    const dsp::Status& status,
    const dsp::Lang& lang) {

  username_ = username;
  email_ = email;
  password_ = password;
  token_ = token;
  given_name_ = given_name;
  family_name_ = family_name;
  status_ = status;
  lang_ = lang;

  id_ = dsp::Identifier(username_.value());
}

/*!
 * Construct user from the provided JSON serialization.
 */
User::User(const nlohmann::json& json_obj) {

  if (json_obj.contains("class") && (json_obj["class"] == "admin::User")) throw dsp::Error(file_, __LINE__, "Deserialization of admin::User failed!");

  if (!json_obj.contains("id")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "id".)");
  id_ = dsp::Identifier(json_obj["id"]);

  if (!json_obj.contains("username")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "username".)");
  username_ = dsp::Username(json_obj["username"]);

  if (!json_obj.contains("email")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "email".)");
  email_ = dsp::Email(json_obj["email"]);

  if (!json_obj.contains("password")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "password".)");
  password_ = dsp::Password(json_obj["password"]);

  if (!json_obj.contains("token")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "token".)");
  token_ = dsp::Token(json_obj["token"]);

  if (!json_obj.contains("given_name")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "given_name".)");
  given_name_ = dsp::GivenName(json_obj["given_name"]);

  if (!json_obj.contains("family_name")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "family_name".)");
  family_name_ = dsp::FamilyName(json_obj["family_name"]);

  if (!json_obj.contains("status")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "status".)");
  status_ = dsp::Status(json_obj["status"]);

  if (!json_obj.contains("lang")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "lang".)");
  lang_ = dsp::Lang(json_obj["lang"]);
}

/*!
 * Serialize the user to GOD (general object description).
 */
nlohmann::json User::to_json() {

  nlohmann::json json_obj = {
      {"class", "admin::User"},
      {"id", id_.to_string()},
      {"username", username_.value()},
      {"email", email_.value()},
      {"password", password_.value()},
      {"token", token_.value()},
      {"given_name", given_name_.value()},
      {"family_name", family_name_.value()},
      {"status", status_.value()},
      {"lang", lang_.value()}
  };

  return json_obj;
}

} // namespace admin
