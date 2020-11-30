//
// Created by Ivan Subotic on 29/11/2020.
//

#include "gtest/gtest.h"

#include "entities/error.h"
#include "username.h"

TEST(UserValuesTest, Username) {
  EXPECT_EQ(entities::user::Username("dduck").value(),"dduck") << "create 'dduck' username";

  // 4 - 50 characters long
  EXPECT_THROW(entities::user::Username("abc"), dsp::Error) << "username has 3 characters";
  EXPECT_NO_THROW(entities::user::Username("root")) << "username has 4 characters";
  EXPECT_NO_THROW(entities::user::Username("12345678901234567890123456789012345678901234567890")) << "username has 50 characters";
  EXPECT_THROW(entities::user::Username("123456789012345678901234567890123456789012345678901"), dsp::Error) << "username has 51 characters";

  // Only contains alphanumeric characters
  EXPECT_THROW(entities::user::Username("abc123._"), dsp::Error) << "username has not allowed characters";
}
