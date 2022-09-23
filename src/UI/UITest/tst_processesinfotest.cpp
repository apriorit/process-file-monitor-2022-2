#include "pch.h"
#include "../processmonitor.h"

using namespace testing;

TEST(ProcessInfoTest, ProcessInfoCheckGreater)
{
    ProcessInfo process1(10,"proc1");
    ProcessInfo process2(5,"proc2");
    EXPECT_EQ(process1 < process2, false);
    EXPECT_EQ(process2 < process1, true);
}

TEST(ProcessInfoTest, ProcessInfoCheckEquality)
{
    ProcessInfo process1(10,"proc1");
    ProcessInfo process2(5,"proc2");
    ProcessInfo process3(10,"proc1");

    EXPECT_EQ(process1 == process2 , false);
    EXPECT_EQ(process1 == process3 , true);
}

TEST(ProcessInfoTest, GetNameFromPath)
{
    ProcessInfo process(10,"C:\\Program files\\ShooterGame.exe");
    EXPECT_EQ(process.Name, "ShooterGame.exe");
}
