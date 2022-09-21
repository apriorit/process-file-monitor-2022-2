#pragma once
#include <QString>

struct ProccessInfo{
    ProccessInfo(int pid,const QString& name)
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
    bool isInjected = false;

    friend bool operator<(const ProccessInfo& first , const ProccessInfo& second);
};



class IProccessMonitor{
public:
    virtual void updateProccessesTable() = 0;
    virtual const ProccessInfo& getProccessInfo(const int index) = 0;
    virtual ~IProccessMonitor();
};

class ProccessMonitor : public IProccessMonitor{

};
