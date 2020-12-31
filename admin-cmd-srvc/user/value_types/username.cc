// Copyright

#include "shared/xsd_types/xsd.h"
#include "username.h"

namespace admin::user {

Username::Username() {

  /**
   * * A valid username has the following restriction:
   * - 4 - 50 characters long
   * - Only contains alphanumeric characters, (underscore, and dot.)
   * (- Underscore and dot can't be at the end or start of a username))
   * (- Underscore or dot can't be used multiple times in a row))
   *
   * regex from scala: ^(?=.{4,50}$)(?![_.])(?!.*[_.]{2})[a-zA-Z0-9._]+(?<![_.])$
   */
  value_.add_restriction(std::make_shared<xsd::RestrictionMinLength>(4, "The minimum Username length is 4."));
  value_.add_restriction(std::make_shared<xsd::RestrictionMaxLength>(50, "The maximum Username length is 50."));
  value_.add_restriction(std::make_shared<xsd::RestrictionPattern>("([a-zA-Z0-9]*)", "Only alphanumeric characters allowed inside an Username."));
}

} // namespace entities::user
