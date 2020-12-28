//
// Created by Ivan Subotic on 23/12/2020.
//

#include "helpers/uuid.h"
#include "identifier.h"


namespace admin::user {

Identifier::Identifier() {
  value_ = uuid::generate_uuid_v4();
}

Identifier::Identifier(const std::string &value) {
  value_ = value;
}

bool Identifier::operator==(const Identifier &rhs) const {
  return static_cast<std::string>(value_) == static_cast<std::string>(rhs.value_);
}

}