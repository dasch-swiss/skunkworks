// Copyright

#include "helpers/xsd_types/xsd.h"
#include "username.h"

namespace entities::user {

Username::Username(const std::string &value) {

  /**
   * * A valid username has the following restriction:
   * - 4 - 50 characters long
   * - Only contains alphanumeric characters, (underscore, and dot.)
   * (- Underscore and dot can't be at the end or start of a username))
   * (- Underscore or dot can't be used multiple times in a row))
   *
   * regex from scala: ^(?=.{4,50}$)(?![_.])(?!.*[_.]{2})[a-zA-Z0-9._]+(?<![_.])$
   */

  std::vector<std::shared_ptr<xsd::Restriction>> restrictions = {
      std::make_shared<xsd::RestrictionMinLength>(4),
      std::make_shared<xsd::RestrictionMaxLength>(50),
      std::make_shared<xsd::RestrictionPattern>("([a-zA-Z0-9])")
  };

  try {
    value_ = xsd::String(value, restrictions);
  } catch (const xsd::Error &e) {
    std::cerr << e << std::endl;
  }

}

} // namespace entities::user
