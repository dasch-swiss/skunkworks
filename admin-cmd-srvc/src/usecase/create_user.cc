//
// Created by Ivan Subotic on 02/01/2021.
//

#include "shared/error/error.h"
#include "create_user.h"

static const char file_[] = __FILE__;

namespace admin {

void CreateUser::create(const std::shared_ptr<User> &user) {

  if (user->is_null()) {
    throw dsp::Error(file_, __LINE__, "Creating an empty user is not allowed!");
  }
  repository_->write(user);
}

}