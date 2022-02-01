//
// Created by dylan liang on 2022/1/29.
//
#include <gtest/gtest.h>
#include "command_printf.h"

TEST(MyTest, Sum)
{
    CommandPrintf cp;

    CommandInput commandInput;
    EXPECT_EQ(cp.matchNumber(" 1323 ",commandInput),true); // PASS
}
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}