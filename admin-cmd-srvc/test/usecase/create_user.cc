//
// Created by Ivan Subotic on 03/01/2021.
//
#include "catch2/catch.hpp"
#include "shared/error/error.h"
#include "admin-cmd-srvc/src/entity/user.h"
#include "admin-cmd-srvc/src/usecase/create_user.h"
#include "admin-cmd-srvc/src/adapter/repository/in_memory_user_repository.h"

TEST_CASE("creating the user", "[usecase][create_user]") {

  std::shared_ptr<admin::InMemoryUserRepository> repo = std::make_shared<admin::InMemoryUserRepository>();
  std::shared_ptr<admin::CreateUser> usecase = std::make_shared<admin::CreateUser>(repo);

  SECTION("empty") {

    std::shared_ptr<admin::User> empty_user = std::make_shared<admin::User>();

    CHECK(empty_user->is_empty());
    CHECK_THROWS_AS(usecase->create(empty_user), dsp::Error);
  }

  SECTION("fully populated") {
    std::shared_ptr<admin::User> full_user = std::make_shared<admin::User>(
      dsp::Username("dduck"),
      dsp::Email("dduck@example.com"),
      dsp::Password("1234"),
      dsp::Token("1234567890"),
      dsp::GivenName("Donald"),
      dsp::FamilyName("Duck"),
      dsp::Status(true),
      dsp::Lang("en"));

    CHECK(!full_user->is_empty());
    CHECK_NOTHROW(usecase->create(full_user));
  }
}
