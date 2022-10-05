#include "pch.h"
#include "mutexguard.h"
#include <iostream>
MutexGuard::MutexGuard(std::mutex& mutexToWatch)
    :watchedMutex(mutexToWatch)
{
    std::cout<<"lock"<<std::endl;
    watchedMutex.lock();
}

MutexGuard::~MutexGuard()
{
    std::cout<<"unlock"<<std::endl;
    watchedMutex.unlock();
}
