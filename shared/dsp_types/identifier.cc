//
// Created by Ivan Subotic on 23/12/2020.
//

#include "shared/uuid.h"
#include "identifier.h"

namespace dsp {

Identifier::Identifier() {
  value_ = uuid::generate_uuid_v4();
}

}