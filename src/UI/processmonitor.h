#pragma once
#include <QString>
#include <set>

struct ProcessInfo{
    ProcessInfo(int pid,const QString& name)
        :Pid{pid},
        Name{name}{}
    const int Pid;
    const QString Name;
    bool readPermission = true;
    bool writePermission = true;
    bool openPermission = true;
    bool closePermission = true;
    bool deletePermission = true;
    bool isMonitored = false;
    bool isDllInjected = false;

    friend bool operator<(const ProcessInfo& first , const ProcessInfo& second);
};

enum class ProcessEditableFields{
    readPerm,
    writePerm,
    openPerm,
    closePerm,
    deletePerm,
    isMonitored,
    isDllInjected
};

class IProcessMonitor{
public:
    virtual void updateProcessesTable() = 0;
    virtual ProcessInfo getCopyOfProcessInfoByIndex(const int Index) = 0;
    virtual ProcessInfo getCopyOfProcessInfoByPid(const int Pid) = 0;
    virtual void setProcessEditableField(const ProcessEditableFields field) = 0;
    virtual ~IProcessMonitor(){}
};

class IGetProcessesInfo{
    virtual std::set<ProcessInfo> getProcessesInfo();
};

class ProcessMonitor : public IProcessMonitor{
public:
    ProcessMonitor(IGetProcessesInfo* getProcessesInfo)
        :getProcessesInfo{getProcessesInfo}{};
    void updateProcessesTable() override;
    ProcessInfo getCopyOfProcessInfoByIndex(const int index) override;
    ProcessInfo getCopyOfProcessInfoByPid(const int Pid) override;
    static std::set<ProcessInfo> mergeProcessesSets(const std::set<ProcessInfo>& oldSet ,
                                                    const std::set<ProcessInfo>& newSet);
    void setProcessEditableField(const ProcessEditableFields field) override;
    ~ProcessMonitor();
private:
    std::set<ProcessInfo> processesInfo;
    IGetProcessesInfo* getProcessesInfo;
};
