#include <iostream>
#include "ProcessManagement.hpp"
#include <windows.h>
#include <cstring>
#include "../encryptDecrypt/Cryption.hpp"

ProcessManagement::ProcessManagement() {
    itemsSemaphore = CreateSemaphore(nullptr, 0, 1000, "items_semaphore");
    emptySlotsSemaphore = CreateSemaphore(nullptr, 1000, 1000, "empty_slots_semaphore");
    
    shmHandle = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(SharedMemory), SHM_NAME);
    sharedMem = static_cast<SharedMemory *>(MapViewOfFile(shmHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedMemory)));
    
    sharedMem->front = 0;
    sharedMem->rear = 0;
    sharedMem->size = 0;
}

ProcessManagement::~ProcessManagement() {
    UnmapViewOfFile(sharedMem);
    CloseHandle(shmHandle);
}

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task) {
    WaitForSingleObject(emptySlotsSemaphore, INFINITE);
    
    std::lock_guard<std::mutex> lock(queueLock);

    if (sharedMem->size >= 1000) {
        return false;
    }
    strcpy(sharedMem->tasks[sharedMem->rear], task->toString().c_str());
    sharedMem->rear = (sharedMem->rear + 1) % 1000;
    sharedMem->size++;

    ReleaseSemaphore(itemsSemaphore, 1, nullptr);

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(nullptr, "executeTask", nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
        return false;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    
    return true;
}

void ProcessManagement::executeTask() {
    WaitForSingleObject(itemsSemaphore, INFINITE);

    std::lock_guard<std::mutex> lock(queueLock);
    char taskStr[256];
    strcpy(taskStr, sharedMem->tasks[sharedMem->front]);
    sharedMem->front = (sharedMem->front + 1) % 1000;
    sharedMem->size--;

    ReleaseSemaphore(emptySlotsSemaphore, 1, nullptr);
    
    executeCryption(taskStr);
}
