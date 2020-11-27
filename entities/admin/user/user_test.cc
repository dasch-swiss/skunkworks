//
// Created by Ivan Subotic on 27/11/2020.
//

#include "gtest/gtest.h"

#include "user.h"

TEST(UserTest, CreateUser) {
  dsp::User user = dsp::User("dduck", "dduck@example.com", "1234", "none", "Donald", "Duck", "none", "en");
  EXPECT_EQ(user.username(),"dduck");
  EXPECT_EQ(user.email(),"dduck@example.com");
}