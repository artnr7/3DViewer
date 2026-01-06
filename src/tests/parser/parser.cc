#include <gtest/gtest.h>
#include "model.h"

TEST(EmptyParser, EmptyTest) {
  EXPECT_TRUE(true);
  s21::A a;
  EXPECT_TRUE(a.print1());
}
