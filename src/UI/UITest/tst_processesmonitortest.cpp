#include "pch.h"
#include "../processmonitor.h"
#include "../processesseeker.h"

using namespace testing;

class ProcessesSeekerMock : public IProcessesSeeker{
public:
    MOCK_METHOD(std::vector<ProcessInfo>, getSystemProcesses ,() , (override) );
};

bool BothProcessesListsEquals(const std::vector<ProcessInfo>& v1,
                              const std::vector<ProcessInfo>& v2){
    if(v1.size() != v2.size()){
        return false;
    }
    for(DWORD i = 0 ; i < v1.size() ; i++){
        if(!(v1[i] == v2[i] && v1[i].settingsEquals(v2[i]))){
            return false;
        }
    }
    return true;
}

TEST(ProcessMonitorTest, BothProcessesListEquals){
    ProcessInfo p1(1,"proc1");
    p1.isDllInjected = true;
    ProcessInfo p2(2,"proc1");
    std::vector<ProcessInfo> v1{p1,p2};
    std::vector<ProcessInfo> v2{p1,p2};

    EXPECT_EQ(BothProcessesListsEquals(v1,v2), true);
}

TEST(ProcessMonitorTest, BothProcessesListNotEqualsDueToPermissions){
    ProcessInfo p1(1,"proc1");
    ProcessInfo p2(2,"proc1");
    std::vector<ProcessInfo> v1{p1,p2};
    std::vector<ProcessInfo> v2{p1,p2};
    v1[0].deletePermission = false;

    EXPECT_EQ(BothProcessesListsEquals(v1,v2), false);
}

TEST(ProcessMonitorTest, BothProcessesListNotEqualsDueToProcesses){
    ProcessInfo p1(1,"proc1");
    ProcessInfo p2(2,"proc1");
    ProcessInfo p3(3,"proc3");
    std::vector<ProcessInfo> v1{p1,p2};
    std::vector<ProcessInfo> v2{p1,p3};

    EXPECT_EQ(BothProcessesListsEquals(v1,v2), false);
}

TEST(ProcessMonitorTest, BothProcessesListNotEqualsDueToDiffrentName){
    ProcessInfo p1(1,"proc1");
    ProcessInfo p2(2,"proc1");
    ProcessInfo p3(1,"proc2");
    std::vector<ProcessInfo> v1{p1,p2};
    std::vector<ProcessInfo> v2{p3,p2};

    EXPECT_EQ(BothProcessesListsEquals(v1,v2), false);
}


TEST(ProcessMonitorTest, processesSeekerWillBeCalledOnce){
    ProcessesSeekerMock processesSeeker;
    ProcessMonitor sut(&processesSeeker);

    EXPECT_CALL(processesSeeker, getSystemProcesses)
            .WillOnce(Return(std::vector<ProcessInfo>()));

    sut.updateProcessesTable();
}

TEST(ProcessMonitorTest, mergeProcessesBothEquals){
    std::vector<ProcessInfo> processes({{1,"p1"},{2,"p2"}});
    std::vector<ProcessInfo> update({{1,"p1"},{2,"p2"}});
    std::vector<ProcessInfo> expected({{1,"p1"},{2,"p2"}});
    std::vector<ProcessInfo> result = ProcessMonitor::mergeProcessesLists(processes, update);

    EXPECT_EQ(result == expected , true);
}

TEST(ProcessMonitorTest, mergeProcessesBothEqualsSaveOldSettings){
    ProcessInfo processInfo(10,"C:\\Berserk.exe");
    processInfo.deletePermission = false;
    processInfo.readPermission = false;
    processInfo.isDllInjected = true;

    std::vector<ProcessInfo> processes({processInfo,{2,"p2"}});
    std::vector<ProcessInfo> update({{10,"C:\\Berserk.exe"},{2,"p2"}});

    std::vector<ProcessInfo> expected({processInfo,{2,"p2"}});
    std::vector<ProcessInfo> result = ProcessMonitor::mergeProcessesLists(processes, update);

    EXPECT_EQ(BothProcessesListsEquals(result,expected), true);
}

TEST(ProcessMonitorTest, mergeProcessesNewProcessesBorned){
    std::vector<ProcessInfo> processes({{1,"p1"},{2,"p2"}});
    std::vector<ProcessInfo> update({{1,"p1"},{2,"p2"},{3,"p3"},{4,"p4"}});

    std::vector<ProcessInfo> expected({{1,"p1"},{2,"p2"},{3,"p3"},{4,"p4"}});
    std::vector<ProcessInfo> result = ProcessMonitor::mergeProcessesLists(processes, update);

    EXPECT_EQ(result, expected);
}

TEST(ProcessMonitorTest, mergeProcessesNewProcessUnderTheSamePid){
    std::vector<ProcessInfo> processes({{1,"p1"},{2,"p2"}});
    std::vector<ProcessInfo> update({{1,"p1"},{2,"p22"}});

    std::vector<ProcessInfo> expected({{1,"p1"},{2,"p22"}});
    std::vector<ProcessInfo> result = ProcessMonitor::mergeProcessesLists(processes, update);

    EXPECT_EQ(result, expected);
}

TEST(ProcessMonitorTest, mergeProcessesOldProcessesTerminated){
    std::vector<ProcessInfo> processes({{1,"p1"},{2,"p2"},{3,"p3"},{4,"p4"}});
    std::vector<ProcessInfo> update({{1,"p1"},{2,"p2"}});

    std::vector<ProcessInfo> expected({{1,"p1"},{2,"p2"}});
    std::vector<ProcessInfo> result = ProcessMonitor::mergeProcessesLists(processes, update);

    EXPECT_EQ(result, expected);
}

