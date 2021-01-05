//
// Created by Ivan Subotic on 03/01/2021.
//

#include "shared/error/error.h"
#include "in_memory_user_repository.h"

static const char file_[] = __FILE__;

namespace admin {

void InMemoryUserRepository::write(const std::shared_ptr<User> &user) {

  if (user->is_null()) {
    throw dsp::Error(file_, __LINE__, "Writing an empty user to the repository not allowed!");
  }

  repository_[user->id()] = user->to_god();
}

std::shared_ptr<User> InMemoryUserRepository::read(const std::string &id) {

  std::string serialized_user;
  if (repository_.find(id) != repository_.end()) {
    serialized_user = repository_[id];
  } else {
    throw dsp::Error(file_, __LINE__, "User not found in repository. Could not read!");
  }

  std::shared_ptr<User> user = std::make_shared<User>(serialized_user);
  return user;
}

void InMemoryUserRepository::remove(const std::string &id) {

  if (repository_.find(id) != repository_.end()) {
    throw dsp::Error(file_, __LINE__, "User not found in repository. Could not remove!");
  }

  repository_.erase(id);
}

}