//
// Created by Ivan Subotic on 14/01/2021.
//

#include "catch2/catch.hpp"
#include "shared/error/error.h"
#include "admin-cmd-srvc/src/entity/user.h"
#include "admin-cmd-srvc/src/adapter/repository/in_memory_user_repository.h"

TEST_CASE("the in_memory repository implementation", "[adapter][repository][in_memory_user_repository]") {

  std::shared_ptr<admin::InMemoryUserRepository> repo = std::make_shared<admin::InMemoryUserRepository>();
  std::shared_ptr<admin::User> full_user = std::make_shared<admin::User>(
      dsp::Username("dduck"),
      dsp::Email("dduck@example.com"),
      dsp::Password("1234"),
      dsp::Token("1234567890"),
      dsp::GivenName("Donald"),
      dsp::FamilyName("Duck"),
      dsp::Status(true),
      dsp::Lang("en"));

  SECTION("should not allow to store an incorrect user") {
    std::shared_ptr<admin::User> empty_user = std::make_shared<admin::User>();
    CHECK_THROWS_AS(repo->create(empty_user), dsp::Error);
  }

  SECTION("should allow to store a correct user") {
    CHECK(!full_user->is_empty());
    CHECK_NOTHROW(repo->create(full_user));
  }

  SECTION("should allow to read the previously stored user") {
    std::string stored_user_id = full_user->id();
    CHECK_NOTHROW(repo->read(stored_user_id));

    std::shared_ptr<admin::User> retrieved_user = repo->read(stored_user_id);
    CHECK(retrieved_user == full_user);
  }
}
