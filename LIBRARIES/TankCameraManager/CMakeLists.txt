cmake_minimum_required(VERSION 3.28)
project(TankCameraManager)

set(CMAKE_CXX_STANDARD 11)

# Add include directories
INCLUDE_DIRECTORIES(../ServoDriverPCA9685/)
INCLUDE_DIRECTORIES(../../../../Arduino/libraries/Adafruit_PWM_Servo_Driver_Library/)
INCLUDE_DIRECTORIES(../../../../Arduino/libraries/Adafruit_BusIO/)

add_executable(TankCameraManager
        TankCameraManager.h
        TankCameraManager.cpp)
