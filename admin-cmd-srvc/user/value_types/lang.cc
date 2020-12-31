//
// Created by Ivan Subotic on 23/12/2020.
//

#include <string>
#include "shared/xsd_types/xsd.h"

#include "lang.h"

namespace admin::user {

Lang::Lang() {
  std::set<std::string> supported_languages = {"en", "de", "fr", "it", "rm"};
  value_.add_restriction(std::make_shared<xsd::RestrictionEnumeration>(supported_languages));
}

}