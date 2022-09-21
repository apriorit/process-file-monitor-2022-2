
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../proccessmonitor.h"
using namespace testing;

TEST(ProccessMonitorTest, ProccessInfoCheckEquality)
{
    ProccessInfo proccess1(10,"proc1");
    ProccessInfo proccess2(5,"proc2");
    EXPECT_EQ(proccess1 < proccess2, false);
    EXPECT_EQ(proccess2 < proccess1, true);
}
