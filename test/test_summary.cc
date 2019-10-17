#include <iostream>
#include "gtest/gtest.h"

#include "testfile.h"

TEST(DummyTest, CheckEquality) {
  int i = 3;
  EXPECT_EQ(3, i);

  i = 12;
  EXPECT_EQ(15,i);
}
