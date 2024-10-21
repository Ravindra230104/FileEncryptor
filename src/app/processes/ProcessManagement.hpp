#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include "Task.hpp"
#include <iostream>
#include <memory>
#include <mutex>
#include <windows.h>

class ProcessManagement {
private:
    struct SharedMemory {
        int size;
        char tasks[1000][256];
        int front;
        int rear;
    };

    HANDLE itemsSemaphore;
    HANDLE emptySlotsSemaphore;
    HANDLE shmHandle;
    SharedMemory* sharedMem;
    const char* SHM_NAME = "Local\\my_queue";
    std::mutex queueLock;

public:
    ProcessManagement();
    ~ProcessManagement();

    bool submitToQueue(std::unique_ptr<Task> task);
    void executeTask();
};

#endif
