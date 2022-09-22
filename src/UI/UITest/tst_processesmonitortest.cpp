
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include "../processmonitor.h"
#include "../processesseeker.h"
#include <set>
using namespace testing;

class ProcessesSeekerMock : public IProcessesSeeker{
public:
    MOCK_METHOD(std::set<ProcessInfo>, getSetOfSystemProcesses ,() , (override) );
};

TEST(ProcessMonitorTest, processesSeekerWillBeCalledOnce){
    ProcessesSeekerMock processesSeeker;
    ProcessMonitor sut(&processesSeeker);

    EXPECT_CALL(processesSeeker, getSetOfSystemProcesses)
            .WillOnce(Return(std::set<ProcessInfo>()));

    sut.updateProcessesTable();
};

TEST(ProcessMonitorTest, mergeProcessesBothEquals){
    std::set<ProcessInfo> processes({{1,"p1"},{2,"p2"}});
    std::set<ProcessInfo> update({{1,"p1"},{2,"p2"}});
    std::set<ProcessInfo> expected({{1,"p1"},{2,"p2"}});
    std::set<ProcessInfo> result = ProcessMonitor::mergeProcessesSets(processes, update);

    EXPECT_EQ(result == expected,true);
};
