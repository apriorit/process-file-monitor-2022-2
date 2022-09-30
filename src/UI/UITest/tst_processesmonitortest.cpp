#include "pch.h"
#include "../processmonitor.h"
#include "../processesseeker.h"
#include "processmonitortestingutility.h"
using namespace testing;

class ProcessMonitorTest : public ::testing::Test{
protected:
    ProcessMonitorTest()
        :firstUpdate{{1,"FirstProcess"},{2,"SecondProcess"},{3,"ThirdProcess"}},
        secondUpdate{{1,"FirstDiffrentProcess"},{3,"ThirdProcess"},{4,"ForthProcess"}},
        processesSeeker{}{}
    ProcessesStorage firstUpdate;
    ProcessesStorage secondUpdate;
    ProcessesStorage sutStorage;
    pmtu::ProcessesSeekerMock processesSeeker;
};

TEST_F(ProcessMonitorTest, IProcessesSeekerReturnsElementsInRandomOrder){
    ProcessMonitor sut(&processesSeeker);
    ProcessesStorage notSortedUpdate({{4, "ForthProcess"}, {2, "SecondProcess"}, {1, "FirstProcess"}});
    ProcessesStorage expected({{1,"FirstProcess"},{2,"SecondProcess"},{4,"ForthProcess"}});
    EXPECT_CALL(processesSeeker, getSystemProcesses)
            .WillOnce(Return(firstUpdate))
            .WillOnce(Return(notSortedUpdate));

    sut.updateProcessesTable();
    sut.updateProcessesTable();

    ASSERT_EQ(sut.getProcessesCount(), expected.getSize());
    for(size_t i = 0; i < sut.getProcessesCount() ; i++){
        EXPECT_EQ(sut.getCopyOfProcessInfoByIndex(i), expected.getProcessByIndex(i));
    }
}

TEST_F(ProcessMonitorTest, getProcessByIndex){
    ProcessMonitor sut(&processesSeeker);
    auto expected = firstUpdate.getProcessByIndex(0);
    EXPECT_CALL(processesSeeker, getSystemProcesses)
            .WillOnce(Return(firstUpdate));

    sut.updateProcessesTable();
    auto result = sut.getCopyOfProcessInfoByIndex(0);

    EXPECT_EQ(expected,result);
}

TEST_F(ProcessMonitorTest, getAndchangeProcessSettingByPid){
    ProcessMonitor sut(&processesSeeker);
    auto expected = firstUpdate.getProcessByIndex(0);
    expected.isDllInjected = true;
    EXPECT_CALL(processesSeeker, getSystemProcesses)
            .WillOnce(Return(firstUpdate));

    sut.updateProcessesTable();
    sut.setProcessEditableFieldByPid(1, ProcessEditableFields::isDllInjected, true);

    EXPECT_EQ(expected.settingsEquals(sut.getCopyOfProcessInfoByPid(1)), true);
}

TEST_F(ProcessMonitorTest, getAndchangeProcessSettingByIndex){
    ProcessMonitor sut(&processesSeeker);
    auto expected = firstUpdate.getProcessByIndex(0);
    expected.openPermission = false;
    EXPECT_CALL(processesSeeker, getSystemProcesses)
            .WillOnce(Return(firstUpdate));

    sut.updateProcessesTable();
    sut.setProcessEditableFieldByIndex(0, ProcessEditableFields::openPerm, false);

    EXPECT_EQ(expected.settingsEquals(sut.getCopyOfProcessInfoByIndex(0)), true);
}

TEST_F(ProcessMonitorTest, UpdateProcessesAndCheckCountOfThem){
    ProcessMonitor sut(&processesSeeker);
    EXPECT_CALL(processesSeeker, getSystemProcesses)
            .WillOnce(Return(firstUpdate));

    sut.updateProcessesTable();

    EXPECT_EQ(sut.getProcessesCount(), secondUpdate.getSize());
}
