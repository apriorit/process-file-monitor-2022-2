
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../processmonitor.h"
using namespace testing;

TEST(ProcessMonitorTest, ProcessInfoCheckEquality)
{
    ProcessInfo process1(10,"proc1");
    ProcessInfo process2(5,"proc2");
    EXPECT_EQ(process1 < process2, false);
    EXPECT_EQ(process2 < process1, true);
}
