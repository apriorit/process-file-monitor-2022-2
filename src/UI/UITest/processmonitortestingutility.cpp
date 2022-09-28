#include "pch.h"
#include "processmonitortestingutility.h"


namespace pmtu{
    bool BothProcessesListsEquals( IProcessesStorage& s1,
                               IProcessesStorage& s2){
        if(s1.getSize() != s2.getSize()){
            return false;
        }
        for(size_t i = 0 ; i < s1.getSize() ; i++){
            const ProcessInfo& proc1 = s1.getProcessByIndex(i);
            const ProcessInfo& proc2 = s2.getProcessByIndex(i);
            if(!(proc1 == proc2 && proc1.settingsEquals(proc2))){
                return false;
            }
        }
        return true;
    }
}
