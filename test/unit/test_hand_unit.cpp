/*test_hand_unit.cpp*/

//
// poker-engine unit tests for hand evaluation
//
// William Brittian
// 2025
//

#include <gtest/gtest.h>

#include "../../src/utils/functions.hpp"

TEST(FunctionsTest, IsInteger) {
    EXPECT_TRUE(isInteger("5"));
    EXPECT_TRUE(isInteger("20 "));
    EXPECT_FALSE(isInteger("hello"));
}