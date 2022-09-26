#include "pch.h"
#include "../processinfo.h"

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

TEST(ProcessInfoTest, SettingsEqualsALL){
    ProcessInfo process1(10,"C:\\GAMES\\MGRR.exe");
    process1.deletePermission = false;
    process1.openPermission = false;
    process1.writePermission = false;
    process1.readPermission = false;
    process1.isDllInjected = true;
    process1.isMonitored = true;
    ProcessInfo process2(10,"C:\\GAMES\\MGRR.exe");
    process2.deletePermission = false;
    process2.openPermission = false;
    process2.writePermission = false;
    process2.readPermission = false;
    process2.isDllInjected = true;
    process2.isMonitored = true;

    EXPECT_EQ(process1.settingsEquals(process2), true);
}

TEST(ProcessInfoTest, SettingsNotEqualsAll){
    ProcessInfo process1(10, "C:\\whatever.exe");
    process1.deletePermission = false;
    process1.openPermission = false;
    process1.writePermission = false;
    process1.readPermission = false;
    process1.isDllInjected = true;
    process1.isMonitored = true;
    ProcessInfo process2(10 , "C:\\whatever.exe");
    process2.deletePermission = true;
    process2.openPermission = true;
    process2.writePermission = true;
    process2.readPermission = true;
    process2.isDllInjected = false;
    process2.isMonitored = false;

    EXPECT_EQ(process1.settingsEquals(process2), false);
}
