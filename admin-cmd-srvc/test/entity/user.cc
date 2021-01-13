//
// Created by Ivan Subotic on 27/11/2020.
//

#include "catch2/catch.hpp"

#include "shared/error/error.h"
#include "admin-cmd-srvc/src/entity/user.h"

TEST_CASE("creating the user and getting all value", "[entities][user]") {

  SECTION("create user") {

    admin::User empty_user = admin::User();
    CHECK(empty_user.is_null());

    admin::User user = admin::User(
        dsp::Username("dduck"),
        dsp::Email("dduck@example.com"),
        dsp::Password("1234"),
        dsp::Token("1234567890"),
        dsp::GivenName("Donald"),
        dsp::FamilyName("Duck"),
        dsp::Status(true),
        dsp::Lang("en"));

    CHECK(user.username() == "dduck");
    CHECK(user.email() == "dduck@example.com");
    CHECK(user.password() == "1234");
    CHECK(user.token() == "1234567890");
    CHECK(user.given_name() == "Donald");
    CHECK(user.family_name() == "Duck");
    CHECK(user.status());
    CHECK(user.lang() == "en");
  }
}
