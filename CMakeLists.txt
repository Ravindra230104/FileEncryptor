cmake_minimum_required(VERSION 3.10)  # Specify the minimum CMake version required
project(Encryptor)                      # Set your project name

# Set C++ standard and enable GNU extensions
set(CMAKE_CXX_STANDARD 11)              # Set C++11 as the standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Make it a required standard
set(CMAKE_CXX_EXTENSIONS ON)            # Enable GNU extensions

# Add your executable and source files
add_executable(main main.cpp src/app/processes/ProcessManagement.cpp)
# Add other source files as needed
