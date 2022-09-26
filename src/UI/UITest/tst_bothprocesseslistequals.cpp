#include "pch.h"
#include "../processinfo.h"
#include "processmonitortestingutility.h"

TEST(BothProcessesListsEqualsTest, ProcessesListGotUpdatedForFirstTime){
    ProcessInfo p1(1,"proc1");
    p1.isDllInjected = true;
    ProcessInfo p2(2,"proc1");
    std::vector<ProcessInfo> v1{p1,p2};
    std::vector<ProcessInfo> v2{p1,p2};

    EXPECT_EQ(pmtu::BothProcessesListsEquals(v1,v2), true);
}

TEST(BothProcessesListsEqualsTest, BothProcessesListEquals){
    ProcessInfo p1(1,"proc1");
    p1.isDllInjected = true;
    ProcessInfo p2(2,"proc1");
    std::vector<ProcessInfo> v1{p1,p2};
    std::vector<ProcessInfo> v2{p1,p2};

    EXPECT_EQ(pmtu::BothProcessesListsEquals(v1,v2), true);
}

TEST(BothProcessesListsEqualsTest, BothProcessesListNotEqualsDueToPermissions){
    ProcessInfo p1(1,"proc1");
    ProcessInfo p2(2,"proc1");
    std::vector<ProcessInfo> v1{p1,p2};
    std::vector<ProcessInfo> v2{p1,p2};
    v1[0].deletePermission = false;

    EXPECT_EQ(pmtu::BothProcessesListsEquals(v1,v2), false);
}

TEST(BothProcessesListsEqualsTest, BothProcessesListNotEqualsDueToProcesses){
    ProcessInfo p1(1,"proc1");
    ProcessInfo p2(2,"proc1");
    ProcessInfo p3(3,"proc3");
    std::vector<ProcessInfo> v1{p1,p2};
    std::vector<ProcessInfo> v2{p1,p3};

    EXPECT_EQ(pmtu::BothProcessesListsEquals(v1,v2), false);
}

TEST(BothProcessesListsEqualsTest, BothProcessesListNotEqualsDueToDiffrentName){
    ProcessInfo p1(1,"proc1");
    ProcessInfo p2(2,"proc1");
    ProcessInfo p3(1,"proc2");
    std::vector<ProcessInfo> v1{p1,p2};
    std::vector<ProcessInfo> v2{p3,p2};

    EXPECT_EQ(pmtu::BothProcessesListsEquals(v1,v2), false);
}
