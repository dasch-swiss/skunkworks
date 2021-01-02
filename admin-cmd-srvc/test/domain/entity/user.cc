//
// Created by Ivan Subotic on 27/11/2020.
//

#include "catch2/catch.hpp"

#include "shared/error/error.h"
#include "admin-cmd-srvc/src/domain/entity/user.h"

TEST_CASE("creating the user and getting all value", "[entities][user]") {
  using namespace admin::entity;

  SECTION("create email") {
    User user = User(std::make_shared<dsp::Username>("dduck"),
                     std::make_shared<dsp::Email>("dduck@example.com"),
                     std::make_shared<dsp::Password>("1234"),
                     std::make_shared<dsp::Token>("1234567890"),
                     std::make_shared<dsp::GivenName>("Donald"),
                     std::make_shared<dsp::FamilyName>("Duck"),
                     std::make_shared<dsp::Status>(true),
                     std::make_shared<dsp::Lang>("en"));

    CHECK(user.username() == "dduck");
    CHECK(user.email() == "dduck@example.com");
    CHECK(user.password() == "1234");
    CHECK(user.token() == "1234567890");
    CHECK(user.given_name() == "Donald");
    CHECK(user.family_name() == "Duck");
    CHECK(user.status() == true);
    CHECK(user.lang() == "en");
  }
}
