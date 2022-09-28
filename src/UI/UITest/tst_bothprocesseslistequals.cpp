#include "pch.h"
#include "../processesstorage.h"
#include "processmonitortestingutility.h"

TEST(BothProcessesListsEqualsTest, BothProcessesListEquals){
    ProcessInfo p1(1,"proc1");
    p1.isDllInjected = true;
    ProcessInfo p2(2,"proc1");
    ProcessesStorage v1;
    v1.add(p1);v1.add(p2);
    ProcessesStorage v2;
    v2.add(p1);v2.add(p2);

    EXPECT_EQ(pmtu::BothProcessesListsEquals(v1,v2), true);
}

TEST(BothProcessesListsEqualsTest, BothProcessesListNotEqualsDueToPermissions){
    ProcessInfo p1(1,"proc1");
    p1.isDllInjected = true;
    ProcessInfo p2(2,"proc1");
    ProcessesStorage v1;
    v1.add(p1);v1.add(p2);
    ProcessesStorage v2;
    v2.add(p1);v2.add(p2);

    EXPECT_EQ(pmtu::BothProcessesListsEquals(v1,v2), true);
    v1.getProcessByIndex(0).deletePermission = false;

    EXPECT_EQ(pmtu::BothProcessesListsEquals(v1,v2), false);
}

TEST(BothProcessesListsEqualsTest, BothProcessesListNotEqualsDueToProcesses){
    ProcessInfo p1(1,"proc1");
    ProcessInfo p2(2,"proc1");
    ProcessInfo p3(3,"proc3");
    ProcessesStorage v1;
    v1.add(p1);v1.add(p2);
    ProcessesStorage v2;
    v2.add(p2);v2.add(p3);

    EXPECT_EQ(pmtu::BothProcessesListsEquals(v1,v2), false);
}

TEST(BothProcessesListsEqualsTest, BothProcessesListNotEqualsDueToDiffrentName){
    ProcessInfo p1(1,"proc1");
    ProcessInfo p2(2,"proc1");
    ProcessInfo p3(2,"proc2");
    ProcessesStorage v1;
    v1.add(p1);v1.add(p2);
    ProcessesStorage v2;
    v2.add(p1);v2.add(p3);

    EXPECT_EQ(pmtu::BothProcessesListsEquals(v1,v2), false);
}
