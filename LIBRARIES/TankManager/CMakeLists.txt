cmake_minimum_required(VERSION 3.28)
project(TankManager)

set(CMAKE_CXX_STANDARD 11)

# Add include directories
INCLUDE_DIRECTORIES(../Logger/)
INCLUDE_DIRECTORIES(../MotorDriverL9110/)

add_executable(TankManager main.cpp
        class/TankManager.h
        class/TankManager.cpp)
