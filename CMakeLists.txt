cmake_minimum_required(VERSION 3.10)

# Define the project name
project(BatteryManagementSystem)

# Add the include directory (assuming headers are inside "include/")
include_directories(${PROJECT_SOURCE_DIR}/inc)

# Add the executable and the source files
add_executable(BatteryManagementSystem
	src/main.cpp
	src/BatteryCell.cpp
	src/BatteryPack.cpp
	src/BalancingController.cpp
	src/hw_access.cpp)
