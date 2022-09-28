#pragma once
#include "../processesseeker.h"
#include "../processesstorage.h"

namespace pmtu{
bool BothProcessesListsEquals(IProcessesStorage& s1,
                              IProcessesStorage& s2);

class ProcessesSeekerMock : public IProcessesSeeker{
public:
    MOCK_METHOD(ProcessesStorage, getSystemProcesses ,() , (override) );
};

}
