//
// Created by Ivan Subotic on 02/01/2021.
//

#ifndef SKUNKWORKS_ADMIN_CMD_SRVC_SRC_USECASE_CREATE_USER_H_
#define SKUNKWORKS_ADMIN_CMD_SRVC_SRC_USECASE_CREATE_USER_H_

#include <memory>
#include "admin-cmd-srvc/src/entity/user.h"
#include "admin-cmd-srvc/src/usecase/port/i_user_repository.h"

namespace admin {

class CreateUser {
 public:
  inline CreateUser(const std::shared_ptr<IUserRepository> &repository) { repository_ = repository};d

  void create(const std::shared_ptr<User> &user);

 private:
  std::shared_ptr<IUserRepository> repository_;

};

}

#endif //SKUNKWORKS_ADMIN_CMD_SRVC_SRC_USECASE_CREATE_USER_H_
