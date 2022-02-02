//
// Created by dylan liang on 2022/1/29.
//
#include <gtest/gtest.h>
#include "command_printf.h"

TEST(CommandPrintfTest,ParseNumber)
{
    CommandPrintf cp;

    CommandInput commandInput;
    EXPECT_EQ(cp.matchNumber(" 1323 ",commandInput),true); // PASS
    EXPECT_EQ(cp.matchNumber(" j 1 ",commandInput),false); // PASS
}

TEST(CommandPrintfTest,ParseCommand)
{
    CommandPrintf cp;

    CommandInput commandInput;
    EXPECT_EQ(cp.matchCommand(" j 1 ",commandInput),true); // PASS
    EXPECT_EQ(commandInput.commandNo,"j"); // PASS
    EXPECT_EQ(commandInput.commandContent,"1"); // PASS
    EXPECT_EQ(cp.matchCommand(" n 2 ",commandInput),true); // PASS
    EXPECT_EQ(commandInput.commandNo,"n"); // PASS
    EXPECT_EQ(commandInput.commandContent,"2"); // PASS
    EXPECT_EQ(cp.matchCommand(" n 0 ",commandInput),true); // PASS
    EXPECT_EQ(commandInput.commandNo,"n"); // PASS
    EXPECT_EQ(commandInput.commandContent,"0"); // PASS

    EXPECT_EQ(cp.matchCommand(" n",commandInput),true); // PASS
    EXPECT_EQ(commandInput.commandNo,"n"); // PASS
    EXPECT_EQ(commandInput.commandContent,""); // PASS
    EXPECT_EQ(cp.matchCommand("n",commandInput),true); // PASS
    EXPECT_EQ(commandInput.commandNo,"n"); // PASS
    EXPECT_EQ(commandInput.commandContent,""); // PASS
    EXPECT_EQ(cp.matchCommand(" n ",commandInput),true); // PASS
    EXPECT_EQ(commandInput.commandNo,"n"); // PASS
    EXPECT_EQ(commandInput.commandContent,""); // PASS
    EXPECT_EQ(cp.matchCommand("n ",commandInput),true); // PASS
    EXPECT_EQ(commandInput.commandNo,"n"); // PASS
    EXPECT_EQ(commandInput.commandContent,""); // PASS
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}