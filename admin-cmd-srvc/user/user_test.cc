//
// Created by Ivan Subotic on 27/11/2020.
//

#include "catch2/catch.hpp"

#include "helpers/error.h"
#include "user.h"

TEST_CASE("creating the user and getting all value", "[entities][user]") {
  using namespace admin::user;

  SECTION("create email") {
    User user = User(std::make_shared<Username>("dduck"),
                     std::make_shared<Email>("dduck@example.com"),
                     std::make_shared<Password>("1234"),
                     std::make_shared<Token>("none"),
                     std::make_shared<GivenName>("Donald"),
                     std::make_shared<FamilyName>("Duck"),
                     std::make_shared<Status>(true),
                     std::make_shared<Lang>("en"));

    CHECK(user.username() == "dduck");
    CHECK(user.email() == "dduck@example.com");
    CHECK(user.password() == "1234");
    CHECK(user.token() == "none");
    CHECK(user.given_name() == "Donald");
    CHECK(user.family_name() == "Duck");
    CHECK(user.status() == true);
    CHECK(user.lang() == "en");
  }
}
