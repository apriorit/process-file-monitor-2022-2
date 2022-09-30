#pragma once
#include <windows.h>
#include <QString>

enum class ProcessEditableFields{
    readPerm,
    writePerm,
    openPerm,
    deletePerm,
    isMonitored,
    isDllInjected
};

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
};
