//
// Created by Ivan Subotic on 23/12/2020.
//

#include "helpers/uuid.h"
#include "identifier.h"

namespace admin::user {

Identifier::Identifier() {
  value_ = uuid::generate_uuid_v4();
}

}