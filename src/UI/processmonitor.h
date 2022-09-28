#pragma once
#include <QString>
#include <windows.h>
#include "processesstorage.h"
#include "processinfo.h"

class IProcessesStorage;

class IProcessesSeeker;

class IProcessMonitor{
public:
    virtual void updateProcessesTable() = 0;
    virtual ProcessInfo getCopyOfProcessInfoByIndex(const size_t Index) const = 0;
    virtual ProcessInfo getCopyOfProcessInfoByPid(const DWORD Pid) const = 0;
    virtual void setProcessEditableFieldByIndex(const size_t Index, const ProcessEditableFields field, const bool value) = 0;
    virtual void setProcessEditableFieldByPid(const DWORD Pid, const ProcessEditableFields field, const bool value) = 0;
    virtual size_t getProcessesCount() const = 0;
    virtual ~IProcessMonitor(){}
};

class ProcessMonitor : public IProcessMonitor{
public:
    ProcessMonitor(IProcessesSeeker* processesSeeker);
    void updateProcessesTable() override;
    ProcessInfo getCopyOfProcessInfoByIndex(const size_t index) const override;
    ProcessInfo getCopyOfProcessInfoByPid(const DWORD Pid) const override;
    void setProcessEditableFieldByIndex(const size_t Index, const ProcessEditableFields field, const bool value) override;
    void setProcessEditableFieldByPid(const DWORD Pid, const ProcessEditableFields field, const bool value) override;
    size_t getProcessesCount() const override;
    ~ProcessMonitor();
private:
    std::unique_ptr<IProcessesStorage> processesStorage;
    IProcessesSeeker* processesSeeker;
    void setProcessEditableField(ProcessInfo& process, const ProcessEditableFields field, const bool value);
};
