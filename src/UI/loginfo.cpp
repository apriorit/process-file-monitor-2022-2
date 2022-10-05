#include "loginfo.h"

LogInfo::LogInfo(const DWORD pid):
    pid{pid}{};

bool operator==(const LogInfo& first, const LogInfo& second){
    return  first.filePath == second.filePath&&
            first.operationTime == second.operationTime&&
            first.preview == second.preview&&
            first.fileHandle == second.fileHandle&&
            first.resultOfTheOperation == second.resultOfTheOperation&&
            first.pid == second.pid&&
            first.numberOfBytes == second.numberOfBytes&&
            first.offset == second.offset&&
            first.operationType == second.operationType;
}
