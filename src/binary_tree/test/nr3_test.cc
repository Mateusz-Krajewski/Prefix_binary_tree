/**
 * @file nr3_test.cc
 * @author Mateusz Krajewski (matikrajek42@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-02-08
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <gtest/gtest.h>
#include "../lib.h"

class DataOperationsTest : public ::testing::Test {
 protected:
    void SetUp() override {
        node = NULL;
    }
};

TEST_F(DataOperationsTest, AddUniqueElement) {
    EXPECT_EQ(add(0xffffffff, 1), 0);
    EXPECT_TRUE(node->one != NULL);
    EXPECT_TRUE(node->zero == NULL);
    EXPECT_EQ((node->one->value & 1), 1);
    EXPECT_EQ(node->one->needed_prefix, 1);
}
TEST_F(DataOperationsTest, AddTwoUniqueElement) {
    EXPECT_EQ(add(0xffffffff, 1), 0);
    EXPECT_EQ(add(0xffffffff, 2), 0);
    EXPECT_TRUE(node->one != NULL);
    EXPECT_TRUE(node->zero == NULL);
    EXPECT_EQ((node->one->value & 1), 1);
    EXPECT_EQ(node->one->needed_prefix, 1);
    EXPECT_TRUE(node->one->one != NULL);
    EXPECT_TRUE(node->one->zero == NULL);
    EXPECT_EQ(node->one->one->needed_prefix, 1);
}


TEST_F(DataOperationsTest, SearchElement) {
    EXPECT_EQ(add(0xffffffff, 1), 0);
    EXPECT_EQ(add(0xffffffff, 2), 0);
    EXPECT_EQ(add(0xffffffff, 1), -1);
    EXPECT_EQ(check(0xff121212), 2);
    EXPECT_EQ(check(0x80121212), 1);
    EXPECT_EQ(check(0x00000000), -1);
}

TEST_F(DataOperationsTest, DropSameElement) {
    ASSERT_EQ(add(0xffffffff, 2), 0);
    EXPECT_EQ(del(0xffffffff, 2), 0);
    EXPECT_EQ(del(0xffffffff, 2), -1);
}
TEST_F(DataOperationsTest, DropRandomElement) {
    EXPECT_EQ(del(0x00ff13ff, 2), -1);
    EXPECT_EQ(del(0xf2ff13ff, 2), -1);
}

TEST_F(DataOperationsTest, DroptRandomElement) {
    EXPECT_EQ(del(0xffffffff, 2), -1);
}
