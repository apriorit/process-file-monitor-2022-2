#pragma once
#include <QString>
#include <vector>
#include <windows.h>

class IProcessesSeeker;

struct ProcessInfo{
    ProcessInfo(DWORD pid,const QString& Path);
    DWORD Pid;
    QString Path;
    QString Name;
    bool readPermission = true;
    bool writePermission = true;
    bool openPermission = true;
    bool deletePermission = true;
    bool isMonitored = false;
    bool isDllInjected = false;

    bool settingsEquals(const ProcessInfo& other) const;
    friend bool operator<(const ProcessInfo& first , const ProcessInfo& second);
    friend bool operator==(const ProcessInfo& first , const ProcessInfo& second);
private:
    QString getNameFromThePath();
};

enum class ProcessEditableFields{
    readPerm,
    writePerm,
    openPerm,
    deletePerm,
    isMonitored,
    isDllInjected
};

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
    ProcessMonitor(IProcessesSeeker* processesSeeker)
        :processesSeeker{processesSeeker}{};
    void updateProcessesTable() override;
    ProcessInfo getCopyOfProcessInfoByIndex(const size_t index) const override;
    ProcessInfo getCopyOfProcessInfoByPid(const DWORD Pid) const override;
    void setProcessEditableFieldByIndex(const size_t Index, const ProcessEditableFields field, const bool value) override;
    void setProcessEditableFieldByPid(const DWORD Pid, const ProcessEditableFields field, const bool value) override;
    size_t getProcessesCount() const override;

    static std::vector<ProcessInfo> mergeProcessesSortedLists(const std::vector<ProcessInfo>& oldProcesses ,
                                                    const std::vector<ProcessInfo>& currentProcesses);
    ~ProcessMonitor();
private:
    size_t getIndexOfProcessBySpecyficPid(const DWORD Pid) const;
    std::vector<ProcessInfo> processesInfo;
    IProcessesSeeker* processesSeeker;
};
