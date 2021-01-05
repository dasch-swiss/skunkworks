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
 * Construct user from the the provided GOD serialization.
 */
User::User(const std::string& value) {

  nlohmann::json god_obj = nlohmann::json::parse(value);

  if (god_obj.contains("class") && (god_obj["class"] == "admin::User")) throw dsp::Error(file_, __LINE__, "Deserialization of admin::User failed!");

  if (!god_obj.contains("id")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "id".)");
  id_ = dsp::Identifier(god_obj["id"]);

  if (!god_obj.contains("username")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "username".)");
  username_ = dsp::Username(god_obj["username"]);

  if (!god_obj.contains("email")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "email".)");
  email_ = dsp::Email(god_obj["email"]);

  if (!god_obj.contains("password")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "password".)");
  password_ = dsp::Password(god_obj["password"]);

  if (!god_obj.contains("token")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "token".)");
  token_ = dsp::Token(god_obj["token"]);

  if (!god_obj.contains("given_name")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "given_name".)");
  given_name_ = dsp::GivenName(god_obj["given_name"]);

  if (!god_obj.contains("family_name")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "family_name".)");
  family_name_ = dsp::FamilyName(god_obj["family_name"]);

  if (!god_obj.contains("status")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "status".)");
  status_ = dsp::Status(god_obj["status"]);

  if (!god_obj.contains("lang")) throw dsp::Error(file_, __LINE__, R"(GOD object missing "lang".)");
  lang_ = dsp::Lang(god_obj["lang"]);
}

/*!
 * Serialize the user to GOD (general object description).
 */
std::string User::to_god() {

  nlohmann::json json_obj = {
      {"class", "admin::User"},
      {"id", id_.value()},
      {"username", username_.value()},
      {"email", email_.value()},
      {"password", password_.value()},
      {"token", token_.value()},
      {"given_name", given_name_.value()},
      {"family_name", family_name_.value()},
      {"status", status_.value()},
      {"lang", lang_.value()}
  };

  return json_obj.dump();
}

} // namespace admin
