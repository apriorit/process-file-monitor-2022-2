#include "pch.h"
#include "../loginfo.h"

using namespace testing;

TEST(LogInfoTest, checkIfEquals){
    const DWORD pid = 5;
    LogInfo logInfo1(pid);
    LogInfo logInfo2(pid);

    EXPECT_EQ(logInfo1 == logInfo2, true);
}

TEST(LogInfoTest, checkIfNotEquals){
    const DWORD pid = 5;
    LogInfo logInfo1(pid);
    logInfo1.numberOfBytes = 6;
    LogInfo logInfo2(pid);

    EXPECT_EQ(logInfo1 == logInfo2, false);
}
