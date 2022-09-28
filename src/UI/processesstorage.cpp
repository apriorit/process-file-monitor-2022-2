#include "pch.h"
#include "processesstorage.h"

ProcessesStorage::ProcessesStorage(){};

ProcessesStorage::ProcessesStorage(std::initializer_list<ProcessInfo> list){
    for(auto& process : list){
    processes.emplace(std::make_pair(process.Pid, process));
}
};

ProcessesStorage::~ProcessesStorage(){}

void ProcessesStorage::add(const ProcessInfo&& processInfo){
    const DWORD Pid = processInfo.Pid;
    if(processes.find(Pid) != processes.end()){
        throw std::invalid_argument("Process with given PID already exist in storage !");
    }
    processes.emplace(std::make_pair(Pid,std::move(processInfo)));
}

void ProcessesStorage::add(const ProcessInfo& processInfo){
    const DWORD Pid = processInfo.Pid;
    if(processes.find(Pid) != processes.end()){
        throw std::invalid_argument("Process with given PID already exist in storage !");
    }
    processes.emplace(std::make_pair(Pid,processInfo));
}

void ProcessesStorage::removeByIndex(const size_t index){
    if(index >= getSize()){
        throw std::out_of_range("Index is out of range !");
    }
    auto iterator = processes.begin();
    std::advance(iterator, index);
    processes.erase(iterator);
}

size_t ProcessesStorage::getSize() const{
    return processes.size();
}

ProcessInfo& ProcessesStorage::getProcessByIndex(const size_t index){
    if(index >= getSize()){
        throw std::out_of_range("Index is out of range !");
    }
    auto iterator = processes.begin();
    std::advance(iterator,index);
    return iterator->second;
}

ProcessInfo& ProcessesStorage::getProcessByPid(const DWORD Pid){
    return processes.at(Pid);
}

void ProcessesStorage::update(IProcessesStorage& other){
    size_t myIndex = 0;
    size_t otherIndex = 0;

    while(otherIndex < other.getSize() && myIndex < getSize()){
        ProcessInfo& myProcess = getProcessByIndex(myIndex);
        ProcessInfo& otherProcess = other.getProcessByIndex(otherIndex);

        if(myProcess == otherProcess){
            myIndex++;
            otherIndex++;
        }
        else if(myProcess.Pid == otherProcess.Pid
                && myProcess.Name != myProcess.Name){
            removeByIndex(myIndex);
            add(otherProcess);
            otherIndex++;
            myIndex++;
        }
        else if(myProcess.Pid > otherProcess.Pid){
            add(otherProcess);
            otherIndex++;
        }
        else{
            removeByIndex(myIndex);
        }
    }

    while(otherIndex < other.getSize()){
        ProcessInfo otherProcess = other.getProcessByIndex(otherIndex);
        add(otherProcess);
        otherIndex++;
    }
}
