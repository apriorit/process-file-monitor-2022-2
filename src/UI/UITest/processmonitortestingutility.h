#pragma once
#include "../processesseeker.h"
#include "../processesstorage.h"

namespace pmtu{
bool BothProcessesListsEquals(ProcessesStorage& s1,
                              ProcessesStorage& s2);

class ProcessesSeekerMock : public IProcessesSeeker{
public:
    MOCK_METHOD(ProcessesStorage, getSystemProcesses ,() , (override) );
};

}
