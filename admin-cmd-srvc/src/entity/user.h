//
// Created by Ivan Subotic on 27/11/2020.
//

#ifndef SKUNKWORKS_ENTITIES_ADMIN_USER_USER_H_
#define SKUNKWORKS_ENTITIES_ADMIN_USER_USER_H_

#include <memory>
#include <string>
#include "external/nlohmann/json.hpp"
#include "shared/dsp_types/identifier.h"
#include "shared/dsp_types/username.h"
#include "shared/dsp_types/email.h"
#include "shared/dsp_types/password.h"
#include "shared/dsp_types/token.h"
#include "shared/dsp_types/given_name.h"
#include "shared/dsp_types/family_name.h"
#include "shared/dsp_types/status.h"
#include "shared/dsp_types/lang.h"

namespace admin {

/*!
 * The class represents a user in the system.
 */
class User {
 public:
  /*!
   * Default constructor. Creates an empty user.
   */
   inline User() = default;

  /*!
   * Constructor for creating a fully populated user.
   */
  User(const dsp::Username& username,
       const dsp::Email& email,
       const dsp::Password& password,
       const dsp::Token& token,
       const dsp::GivenName& given_name,
       const dsp::FamilyName& family_name,
       const dsp::Status& status,
       const dsp::Lang& lang);

  /*!
   * Constructor for crating a user from the JSON serialization.
   */
  explicit User(const nlohmann::json& json_obj);

  inline std::string id() { return id_.to_string(); };
  inline std::string username() { return username_.value(); };
  inline std::string email() { return email_.value(); };
  inline std::string password() { return password_.value(); };
  inline std::string token() { return token_.value(); };
  inline std::string given_name() { return given_name_.value(); };
  inline std::string family_name() { return family_name_.value(); };
  inline bool status() { return status_.value(); };
  inline std::string lang() { return lang_.value(); };

  /*!
   * Check the user for null. If the user was only created through
   * the default constructor, then the Identifier is null.
   * @return
   */
  inline bool is_empty() { return id_.to_string() == dsp::Identifier::empty_identifier().to_string(); };

  /*!
   * Serialize user to JSON.
   */
  nlohmann::json to_json();


 private:
  dsp::Identifier id_ = dsp::Identifier::empty_identifier();
  dsp::Username username_;
  dsp::Email email_;
  dsp::Password password_;
  dsp::Token token_;
  dsp::GivenName given_name_;
  dsp::FamilyName family_name_;
  dsp::Status status_;
  dsp::Lang lang_;
};

} // namespace admin

#endif //SKUNKWORKS_ENTITIES_ADMIN_USER_USER_H_
