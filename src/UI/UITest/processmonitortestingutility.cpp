#include "pch.h"
#include "processmonitortestingutility.h"

namespace pmtu{
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
}
