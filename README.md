# Parallel File Encryptor and Decryptor in C++

This project implements parallel encryption and decryption of files using multithreading and multiprocessing concepts of Operating system in C++.

## Table of Contents
- [Project Theory](#project-theory)
  - [Introduction](#introduction)
  - [Basic Working Flow](#basic-working-flow)
  - [Approach](#multi-threading-implementation)
  - [Motivation](#motivation)
  - [Features](#proxy-server-features)
  - [OS Components Used](#os-components-used)
  - [Limitations](#limitations)
  - [Future Enhancements](#future-enhancements)
- [How to Run](#how-to-run)
- [Demo](#demo)


# Project Theory

## Introduction
This project is a parallel file encryption and decryption tool built in C++ using both multithreading and multiprocessing. It efficiently handles tasks by implementing a task queue, enabling concurrent processing of multiple files while securely managing encryption and decryption operations.

## Project Workflow

1. **User Input:**
   - The user provides a file as input, specifying the path to the file they want to encrypt or decrypt.

2. **File Handling (IO Class):**
   - The `IO` class takes the file path provided by the user and reads the file.
   - It returns the file stream, which contains the content to be processed.

3. **Task Submission to Process Management:**
   - The file processing task is submitted to the **Process Management** system.
   - The process management system then submits the task to a **Task Queue**, which is responsible for managing and scheduling tasks.
   - For each task, the task queue creates a child process from the parent process to handle individual file operations.

4. **Encryption/Decryption in Child Processes:**
   - Each child process performs either encryption or decryption on the file content, depending on the task assigned.
   - The parallelism ensures efficient and fast processing of multiple files using multithreading and multiprocessing techniques.

## Approach

### 1. **Multithreading**
- **Multithreading** is implemented to allow multiple threads to run concurrently within the same process. This is particularly useful when performing tasks that involve I/O-bound operations such as reading from or writing to files.
- By dividing the file content into smaller chunks, different threads can handle different parts of the file simultaneously, reducing the time required for encryption or decryption.
- Threads in the program share the same memory space, which allows efficient data sharing, but also requires careful handling of shared resources to avoid race conditions.

### 2. **Multiprocessing**
- **Multiprocessing** is used to achieve true parallelism by spawning separate processes for different tasks. Each process operates in its own memory space, which makes it ideal for CPU-bound tasks, such as encryption and decryption, that require intensive computation.
- The **Process Management** system assigns file operations (encryption or decryption) to separate processes via the **Task Queue**. This ensures that multiple files can be processed simultaneously, with each process running independently.
- The program leverages the ability of processes to work in parallel, utilizing multiple CPU cores for maximum performance.
  
### Key Concepts Implemented:
- **Task Queue:** A queue that manages the scheduling of tasks and distributes them among multiple threads or processes.
- **Semaphores:** Used to control access to shared resources, ensuring synchronization between threads during concurrent execution.
- **Locks:** Mutex locks are implemented to avoid data inconsistency and race conditions when multiple threads access shared data.

  

## Motivation
1. **File Security:** Ensures secure encryption and decryption of sensitive data.
2. **Performance:** Speeds up processing with multithreading and multiprocessing.
3. **OS Concurrency:** Demonstrates practical use of concurrency and process management.


## OS Components Used
- **Threading**: To handle multiple requests simultaneously.
- **Locks**: To manage concurrent data access.
- **Semaphore**: For multi-thread synchronization.
- **Cache**: Uses the **LRU (Least Recently Used)** algorithm for storing frequently accessed data.

## Limitations
1. **Resource Overhead:** The use of multithreading and multiprocessing introduces additional overhead, which can impact performance, especially on systems with limited resources like CPU or memory.

2. **Platform Dependency:** The project is currently designed to run only on Linux-based systems, as it relies on POSIX threads and process management, making it less portable to other operating systems.

## Future Enhancements
- Implement **multiprocessing** for parallelism, improving performance.
- Extend functionality to **restrict specific websites** based on predefined rules.
- Support **POST requests** along with GET.

## How to Run

To run this project, follow these steps:

1. Clone the repository:
    ```bash
    $ git clone  https://github.com/Ravindra230104/FileEncryptor.git
    $ cd encryptor
    ```

2. Build the project:
    ```bash
    $ make all
    ```
    
## Notes:
- **Linux only**: This code runs on Linux machines.
- **Disable browser cache**: Ensure your browser’s cache is disabled while testing the proxy server.
- To run the proxy **without cache**, rename the file `proxy_server_with_cache.c` to `proxy_server_without_cache.c` in the Makefile and rebuild.

## Demo

