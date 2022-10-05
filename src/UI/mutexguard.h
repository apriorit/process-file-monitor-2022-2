#pragma once
#include <mutex>

class MutexGuard{
public:
    MutexGuard(std::mutex& mutexToWatch);
    ~MutexGuard();
private:
    std::mutex& watchedMutex;
};
