#include "proccessmonitor.h"

bool operator<(const ProccessInfo& first , const ProccessInfo& second){
    return first.Pid < second.Pid;
}
