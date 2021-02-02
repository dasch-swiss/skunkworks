//
// Created by Ivan Subotic on 03/01/2021.
//
#include "external/nlohmann/json.hpp"
#include "shared/error/error.h"
#include "in_memory_user_repository.h"

static const char file_[] = __FILE__;

namespace admin {

void InMemoryUserRepository::create(const std::shared_ptr<User> &user) {

  if (user->is_empty()) {
    throw dsp::Error(file_, __LINE__, "Writing an empty user to the repository not allowed!");
  }

  // TODO: check that  user id IS NOT in use

  repository_[user->id()] = user->to_json().dump();
}

void InMemoryUserRepository::update(const std::shared_ptr<User> &user) {

  if (user->is_empty()) {
    throw dsp::Error(file_, __LINE__, "Writing an empty user to the repository not allowed!");
  }

  // TODO: check that user id IS in use

  repository_[user->id()] = user->to_json().dump();
}

std::shared_ptr<User> InMemoryUserRepository::read(const std::string &id) {
  nlohmann::json serialized_user;
  if (repository_.find(id) != repository_.end()) {
    serialized_user = nlohmann::json::parse(repository_[id]);
  } else {
    throw dsp::Error(file_, __LINE__, "Could not read. User not found in repository!");
  }

  std::shared_ptr<User> user = std::make_shared<User>(serialized_user);
  return user;
}

void InMemoryUserRepository::remove(const std::string &id) {

  if (repository_.find(id) != repository_.end()) {
    throw dsp::Error(file_, __LINE__, "Could not remove. User not found in repository!");
  }

  repository_.erase(id);
}

}