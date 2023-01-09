cmake_minimum_required(VERSION 3.23)
project(stud_96)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O0")

add_executable(stud_96 main.cpp ArrUtils.h Timer.h CSVWriter.h TimerHelper.h BSTree.h TestArrUtils.h)
