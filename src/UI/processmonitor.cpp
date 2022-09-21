#include "processmonitor.h"

bool operator<(const ProcessInfo& first , const ProcessInfo& second){
    return first.Pid < second.Pid;
}
