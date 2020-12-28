//
// Created by Ivan Subotic on 27/11/2020.
//

#include "catch2/catch.hpp"

#include "../../entities/error.h"
#include "user.h"
#include "username.h"

TEST_CASE("creating the user and getting all value", "[entities][user]") {
  using namespace entities::user;
  User user = User(std::make_shared<Username>("dduck"),
                   "dduck@example.com",
                   "1234",
                   "none",
                   "Donald",
                   "Duck",
                   "none",
                   "en");
  CHECK(user.username()->value() == std::make_shared<Username>("dduck")->value());
  CHECK(user.email()=="dduck@example.com");
  CHECK(user.password()=="1234");
  CHECK(user.token()=="none");
  CHECK(user.given_name()=="Donald");
  CHECK(user.family_name()=="Duck");
  CHECK(user.family_name()=="Duck");
  CHECK(user.status()=="none");
  CHECK(user.lang()=="en");

  CHECK_THROWS_AS(
      (User(std::make_shared<Username>("dduck"), "", "", "", "", "", "", "")),
      entities::Error
  );

}