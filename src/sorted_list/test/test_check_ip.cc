/**
 * @file test_check_ip.cc
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

TEST(CheckIpTest, IpInSameNetwork) {
    EXPECT_EQ(check_ip(0xC0A80000, 24, 0xC0A80001), 0);  // 192.168.0.0/24 i 192.168.0.1
}

TEST(CheckIpTest, IpOnNetworkBoundary) {
    EXPECT_EQ(check_ip(0xC0A80000, 24, 0xC0A800FF), 0);  // 192.168.0.0/24 i 192.168.0.255
}

TEST(CheckIpTest, IpOutsideNetwork) {
    EXPECT_EQ(check_ip(0xC0A80000, 24, 0xC0A80100), -1);  // 192.168.0.0/24 i 192.168.1.0
}

TEST(CheckIpTest, IpIn16BitNetwork) {
    EXPECT_EQ(check_ip(0xC0A80000, 16, 0xC0A80101), 0);  // 192.168.0.0/16 i 192.168.1.1
}

TEST(CheckIpTest, OutsideWith32Mask) {
    EXPECT_EQ(check_ip(0xC0A80001, 32, 0xC0A80002), -1);  // 192.168.0.1/32 i 192.168.0.2
}

TEST(CheckIpTest, OutsideWith32Mask2) {
    EXPECT_EQ(check_ip(0xA140000, 16, 0xA14FFFE), 0);  // 10.20.0.0/16 i 10.20.255.255
}
TEST(CheckIpTest, OutsideWith32Mask3) {
    EXPECT_EQ(check_ip(0x20408000, 20, 0x204090ff), -1);  // 32.64.128.0/20 i 32.64.144.255
}
TEST(CheckIpTest, OutsideWith32Mask4) {
    EXPECT_EQ(check_ip(0x20408000, 20, 0x20408fff), 0);  // 32.64.128.0/20 i 32.64.143.255
}