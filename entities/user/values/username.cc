// Copyright

#include <regex>
#include "entities/error.h"
#include "username.h"

namespace entities::user {

Username::Username(const std::string& value) {

  /**
   * * A regex that matches a valid username
   * - 4 - 50 characters long
   * - Only contains alphanumeric characters (, underscore and dot).
   * (- Underscore and dot can't be at the end or start of a username)
   * (- Underscore or dot can't be used multiple times in a row)
   */
  // ^(?=.{4,50}$)(?![_.])(?!.*[_.]{2})[a-zA-Z0-9._]+(?<![_.])$
  const static std::regex re("^(?=.{4,50}$)[a-zA-Z0-9]+$");
  std::cmatch match;

  if (std::regex_match(value.c_str(), match, re)) {
    value_ = value;
  } else {
    throw entities::Error(__file__, __LINE__, "Invalid dsp::admin::user::Username value!");
  }

}

} // namespace entities::user
