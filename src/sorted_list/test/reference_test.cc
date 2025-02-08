/**
 * @file reference_test.cc
 * @author Mateusz Krajewski (matikrajek42@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-02-08
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <gtest/gtest.h>
#include "src/nr2/lib.h"

class DataOperationsTest : public ::testing::Test {
 protected:
    void SetUp() override {
        data_lenght = 0;
    }
};

TEST_F(DataOperationsTest, AddUniqueElement) {
    EXPECT_EQ(add(10, 24), 0);
    EXPECT_EQ(data_lenght, 1);
    EXPECT_EQ(data[0].base, 10);
    EXPECT_EQ(data[0].mask, 24);
}

TEST_F(DataOperationsTest, AddDuplicateElement) {
    add(10, 24);
    EXPECT_EQ(add(10, 24), -1);
    EXPECT_EQ(data_lenght, 1);
}

TEST_F(DataOperationsTest, DeleteExistingElement) {
    add(10, 36);
    add(20, 24);
    EXPECT_EQ(del(10, 36), 0);
    EXPECT_EQ(data_lenght, 1);
    EXPECT_EQ(data[0].base, 20);
}

TEST_F(DataOperationsTest, DeleteNonExistingElement) {
    add(10, 24);
    EXPECT_EQ(del(30, 26), -1);
    EXPECT_EQ(data_lenght, 1);
}



