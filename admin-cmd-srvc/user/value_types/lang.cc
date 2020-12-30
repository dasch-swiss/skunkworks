//
// Created by Ivan Subotic on 23/12/2020.
//

#include <string>
#include "shared/xsd_types/xsd.h"

#include "lang.h"

namespace admin::user {

std::set<std::string> supported_languages = {"en", "de", "fr", "it", "rm"};

/*!
 * Creates a language value with the language set to "en" and applied restriction enumeration.
 */
Lang::Lang() {
  value_ = xsd::String("en", std::make_shared<xsd::RestrictionEnumeration>(supported_languages));
}

Lang::Lang(const std::string &value) {
  value_ = xsd::String(value, std::make_shared<xsd::RestrictionEnumeration>(supported_languages));
}

bool Lang::operator==(const Lang &rhs) const {
  return static_cast<std::string>(value_) == static_cast<std::string>(rhs.value_);
}

bool Lang::operator!=(const Lang &rhs) const {
  return static_cast<std::string>(value_) != static_cast<std::string>(rhs.value_);
}

}