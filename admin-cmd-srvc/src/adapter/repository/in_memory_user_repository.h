//
// Created by Ivan Subotic on 03/01/2021.
//

#ifndef SKUNKWORKS_ADMIN_CMD_SRVC_SRC_ADAPTER_REPOSITORY_IN_MEMORY_USER_REPOSITORY_H_
#define SKUNKWORKS_ADMIN_CMD_SRVC_SRC_ADAPTER_REPOSITORY_IN_MEMORY_USER_REPOSITORY_H_

#include <unordered_map>
#include "admin-cmd-srvc/src/usecase/port/i_user_repository.h"

namespace admin {

class InMemoryUserRepository : public IUserRepository {
 public:
  /*!
   * Default constructor.
   */
  inline InMemoryUserRepository() = default;

  /*!
   * Write new user to unordered_map.
   */
  void create(const std::shared_ptr<User> &user);

  /*!
   * Update existing user in unordered_map.
   */
  void update(const std::shared_ptr<User> &user);

  /*!
   * Read user from unordered_map.
   */
  std::shared_ptr<User> read(const std::string &id);

  /*!
   * Remove user from unordered_map.
   * @param id
   */
  void remove(const std::string &id);

 private:
  std::unordered_map<std::string, std::string> repository_;
};

}

#endif //SKUNKWORKS_ADMIN_CMD_SRVC_SRC_ADAPTER_REPOSITORY_IN_MEMORY_USER_REPOSITORY_H_
