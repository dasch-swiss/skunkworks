//
// Created by Ivan Subotic on 27/11/2020.
//

#include "gtest/gtest.h"

#include "entities/error.h"
#include "user.h"

TEST(UserTest, CreateUserSucessfully) {
  entities::user::User user = entities::user::User("dduck", "dduck@example.com", "1234", "none", "Donald", "Duck", "none", "en");
  EXPECT_EQ(user.username(),"dduck");
  EXPECT_EQ(user.email(),"dduck@example.com");
  EXPECT_EQ(user.password(),"1234");
  EXPECT_EQ(user.token(),"none");
  EXPECT_EQ(user.given_name(),"Donald");
  EXPECT_EQ(user.family_name(),"Duck");
  EXPECT_EQ(user.family_name(),"Duck");
  EXPECT_EQ(user.status(),"none");
  EXPECT_EQ(user.lang(),"en");
}

TEST(UserTest, CreateUserWithExceptions) {
  EXPECT_THROW(
      entities::user::User("", "", "", "", "", "", "", ""),
      dsp::Error);
}