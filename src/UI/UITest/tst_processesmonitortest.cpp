#include "pch.h"
#include "../processmonitor.h"
#include "../processesseeker.h"
#include "processmonitortestingutility.h"
using namespace testing;

class ProcessMonitorTest_F : public ::testing::Test{
protected:
    ProcessMonitorTest_F()
        :firstUpdate{{1,"FirstProcess"},{2,"SecondProcess"},{3,"ThirdProcess"}},
        secondUpdate{{1,"FirstDiffrentProcess"},{3,"ThirdProcess"},{4,"ForthProcess"}},
        processesSeeker{}{}
    const std::vector<ProcessInfo> firstUpdate;
    const std::vector<ProcessInfo> secondUpdate;
    pmtu::ProcessesSeekerMock processesSeeker;
};

TEST_F(ProcessMonitorTest_F, IProcessesSeekerReturnsElementsInRandomOrder){
    ProcessMonitor sut(&processesSeeker);
    std::vector<ProcessInfo> notSortedUpdate({{4, "ForthProcess"}, {2, "SecondProcess"}, {1, "FirstProcess"}});
    std::vector<ProcessInfo> expected({{1,"FirstProcess"},{2,"SecondProcess"},{4,"ForthProcess"}});
    EXPECT_CALL(processesSeeker, getSystemProcesses)
            .WillOnce(Return(firstUpdate))
            .WillOnce(Return(notSortedUpdate));

    sut.updateProcessesTable();
    sut.updateProcessesTable();

    ASSERT_EQ(sut.getProcessesCount(), expected.size());
    for(size_t i = 0; i < sut.getProcessesCount() ; i++){
        EXPECT_EQ(sut.getCopyOfProcessInfoByIndex(i), expected[i]);
    }
}

TEST_F(ProcessMonitorTest_F, getProcessByIndex){
    ProcessMonitor sut(&processesSeeker);
    auto expected = firstUpdate[0];
    EXPECT_CALL(processesSeeker, getSystemProcesses)
            .WillOnce(Return(firstUpdate));

    sut.updateProcessesTable();
    auto result = sut.getCopyOfProcessInfoByIndex(0);

    EXPECT_EQ(expected,result);
}

TEST_F(ProcessMonitorTest_F, getAndchangeProcessSettingByPid){
    ProcessMonitor sut(&processesSeeker);
    auto expected = firstUpdate[0];
    expected.isDllInjected = true;
    EXPECT_CALL(processesSeeker, getSystemProcesses)
            .WillOnce(Return(firstUpdate));

    sut.updateProcessesTable();
    sut.setProcessEditableFieldByPid(1, ProcessEditableFields::isDllInjected, true);

    EXPECT_EQ(expected.settingsEquals(sut.getCopyOfProcessInfoByPid(1)), true);
}

TEST_F(ProcessMonitorTest_F, getAndchangeProcessSettingByIndex){
    ProcessMonitor sut(&processesSeeker);
    auto expected = firstUpdate[0];
    expected.openPermission = false;
    EXPECT_CALL(processesSeeker, getSystemProcesses)
            .WillOnce(Return(firstUpdate));

    sut.updateProcessesTable();
    sut.setProcessEditableFieldByIndex(0, ProcessEditableFields::openPerm, false);

    EXPECT_EQ(expected.settingsEquals(sut.getCopyOfProcessInfoByIndex(0)), true);
}

TEST_F(ProcessMonitorTest_F, UpdateProcessesAndCheckCountOfThem){
    ProcessMonitor sut(&processesSeeker);
    EXPECT_CALL(processesSeeker, getSystemProcesses)
            .WillOnce(Return(firstUpdate));

    sut.updateProcessesTable();

    EXPECT_EQ(sut.getProcessesCount(), secondUpdate.size());
}

TEST(ProcessMonitorTest, mergeProcessesBothEquals){
    std::vector<ProcessInfo> processes({{1,"p1"},{2,"p2"}});
    std::vector<ProcessInfo> update({{1,"p1"},{2,"p2"}});
    std::vector<ProcessInfo> expected({{1,"p1"},{2,"p2"}});
    std::vector<ProcessInfo> result = ProcessMonitor::mergeProcessesSortedLists(processes, update);

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
    std::vector<ProcessInfo> result = ProcessMonitor::mergeProcessesSortedLists(processes, update);

    EXPECT_EQ(pmtu::BothProcessesListsEquals(result,expected), true);
}

TEST(ProcessMonitorTest, mergeProcessesNewProcessesBorned){
    std::vector<ProcessInfo> processes({{1,"p1"},{2,"p2"}});
    std::vector<ProcessInfo> update({{1,"p1"},{2,"p2"},{3,"p3"},{4,"p4"}});

    std::vector<ProcessInfo> expected({{1,"p1"},{2,"p2"},{3,"p3"},{4,"p4"}});
    std::vector<ProcessInfo> result = ProcessMonitor::mergeProcessesSortedLists(processes, update);

    EXPECT_EQ(result, expected);
}

TEST(ProcessMonitorTest, mergeProcessesNewProcessUnderTheSamePid){
    std::vector<ProcessInfo> processes({{1,"p1"},{2,"p2"}});
    std::vector<ProcessInfo> update({{1,"p1"},{2,"p22"}});

    std::vector<ProcessInfo> expected({{1,"p1"},{2,"p22"}});
    std::vector<ProcessInfo> result = ProcessMonitor::mergeProcessesSortedLists(processes, update);

    EXPECT_EQ(result, expected);
}

TEST(ProcessMonitorTest, mergeProcessesOldProcessesTerminated){
    std::vector<ProcessInfo> processes({{1,"p1"},{2,"p2"},{3,"p3"},{4,"p4"}});
    std::vector<ProcessInfo> update({{1,"p1"},{2,"p2"}});

    std::vector<ProcessInfo> expected({{1,"p1"},{2,"p2"}});
    std::vector<ProcessInfo> result = ProcessMonitor::mergeProcessesSortedLists(processes, update);

    EXPECT_EQ(result, expected);
}
