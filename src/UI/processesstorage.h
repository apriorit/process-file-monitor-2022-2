#pragma once
#include <map>
#include "processinfo.h"

class IProcessesStorage{
public:
    virtual void add(const ProcessInfo&&) = 0;
    virtual void add(const ProcessInfo&) = 0;
    virtual void removeByIndex(const size_t index) = 0;
    virtual size_t getSize() const = 0;
    virtual ProcessInfo& getProcessByIndex(const size_t index) = 0;
    virtual ProcessInfo& getProcessByPid(const DWORD Pid) = 0;
    virtual void update(IProcessesStorage&) = 0;
    virtual ~IProcessesStorage(){};
};

class ProcessesStorage : public IProcessesStorage{
public:
    ProcessesStorage();
    ProcessesStorage(std::initializer_list<ProcessInfo> list);
    ~ProcessesStorage();
    void add(const ProcessInfo&&) override;
    void add(const ProcessInfo&) override;
    void removeByIndex(const size_t index) override;
    ProcessInfo& getProcessByIndex(const size_t index) override;
    ProcessInfo& getProcessByPid(const DWORD Pid) override;
    size_t getSize() const override;
    void update(IProcessesStorage&) override;

private:
    std::map<DWORD, ProcessInfo> processes;
};
