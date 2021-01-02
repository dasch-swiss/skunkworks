//
// Created by Ivan Subotic on 02/01/2021.
//

#ifndef SKUNKWORKS_ADMIN_CMD_SRVC_SRC_USECASE_PORT_I_USER_REPOSITORY_H_
#define SKUNKWORKS_ADMIN_CMD_SRVC_SRC_USECASE_PORT_I_USER_REPOSITORY_H_

#include <string>
#include "admin-cmd-srvc/src/domain/entity/user.h"

class IUserRepository
{
 public:
  virtual admin::entity::User create(const admin::entity::User &user) = 0;
  virtual std::optional<admin::entity::User> find_by_id(const std::string &id) = 0;
  virtual ~IUserRepository() = default;
};

#endif //SKUNKWORKS_ADMIN_CMD_SRVC_SRC_USECASE_PORT_I_USER_REPOSITORY_H_
