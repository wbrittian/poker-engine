/*test_basic_unit.cpp*/

//
// baseline gtest
//
// William Brittian
// 2025
//

#include <gtest/gtest.h>

TEST(BasicTest, TestTrue) {
    EXPECT_EQ(2, 2);
}