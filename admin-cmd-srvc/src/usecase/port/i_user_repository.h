//
// Created by Ivan Subotic on 02/01/2021.
//

#ifndef SKUNKWORKS_ADMIN_CMD_SRVC_SRC_USECASE_PORT_I_USER_REPOSITORY_H_
#define SKUNKWORKS_ADMIN_CMD_SRVC_SRC_USECASE_PORT_I_USER_REPOSITORY_H_

#include <string>
#include "admin-cmd-srvc/src/entity/user.h"

namespace admin {

/*!
 * This "interface" class should be implemented in the 'adapter layer',
 * allowing the 'usecase layer' to communicate with the repository
 * implementation in the 'adapter layer' for storing and reading the
 * current state.
 */
class IUserRepository
{
 public:
  /*!
   * Write user to repository. Existing user should be overwritten.
   */
  virtual void write(const std::shared_ptr<User> &user) = 0;

  /*!
   * Read user (by id) from repository.
   */
  virtual std::shared_ptr<User> read(const std::string &id) = 0;

  /*!
   * Remove user (by id) from repository.
   */
  virtual void remove(const std::string &id) = 0;

  virtual ~IUserRepository() = default;
};

}

#endif //SKUNKWORKS_ADMIN_CMD_SRVC_SRC_USECASE_PORT_I_USER_REPOSITORY_H_
