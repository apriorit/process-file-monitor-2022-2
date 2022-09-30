#pragma once
#include <map>
#include "processinfo.h"

class ProcessesStorage{
public:
    ProcessesStorage();
    ProcessesStorage(std::initializer_list<ProcessInfo> list);
    ~ProcessesStorage();
    void add(ProcessInfo&&);
    void add(const ProcessInfo&);
    void removeByIndex(const size_t index);
    ProcessInfo& getProcessByIndex(const size_t index);
    ProcessInfo& getProcessByPid(const DWORD Pid);
    size_t getSize() const;
    void update(ProcessesStorage&);

private:
    std::map<DWORD, ProcessInfo> processes;
};
