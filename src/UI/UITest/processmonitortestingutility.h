#pragma once
#include "../processmonitor.h"
#include "../processesseeker.h"

namespace pmtu{
bool BothProcessesListsEquals(const std::vector<ProcessInfo>& v1,
                              const std::vector<ProcessInfo>& v2);

class ProcessesSeekerMock : public IProcessesSeeker{
public:
    MOCK_METHOD(std::vector<ProcessInfo>, getSystemProcesses ,() , (override) );
};

}
