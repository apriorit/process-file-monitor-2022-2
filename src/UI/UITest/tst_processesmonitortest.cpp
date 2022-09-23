
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <iostream>
#include "../processmonitor.h"
#include "../processesseeker.h"

using namespace testing;

class ProcessesSeekerMock : public IProcessesSeeker{
public:
    MOCK_METHOD(std::vector<ProcessInfo>, getSystemProcesses ,() , (override) );
};

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
    processInfo.closePermission = false;
    processInfo.deletePermission = false;
    processInfo.readPermission = false;
    processInfo.isDllInjected = true;

    std::vector<ProcessInfo> processes({processInfo,{2,"p2"}});
    std::vector<ProcessInfo> update({{10,"C:\\Berserk.exe"},{2,"p2"}});

    std::vector<ProcessInfo> expected({processInfo,{2,"p2"}});
    std::vector<ProcessInfo> result = ProcessMonitor::mergeProcessesLists(processes, update);

    EXPECT_EQ(result, expected);
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

