
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
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
};

TEST(ProcessMonitorTest, mergeProcessesBothEquals){
    std::vector<ProcessInfo> processes({{1,"p1"},{2,"p2"}});
    std::vector<ProcessInfo> update({{1,"p1"},{2,"p2"}});
    std::vector<ProcessInfo> expected({{1,"p1"},{2,"p2"}});
    std::vector<ProcessInfo> result = ProcessMonitor::mergeProcessesLists(processes, update);

    EXPECT_EQ(result == expected,true);
};

