/*test_functions_unit.cpp*/

//
// poker-engine unit tests for helper functions
//
// William Brittian
// 2025
//

#include <gtest/gtest.h>

#include "../../src/functions.h"

TEST(FunctionsTest, IsInteger) {
    EXPECT_EQ(isInteger("5"), true);
    EXPECT_EQ(isInteger("20 "), true);
    EXPECT_EQ(isInteger("hello"), false);
}