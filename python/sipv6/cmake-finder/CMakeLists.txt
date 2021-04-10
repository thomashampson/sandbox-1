cmake_minimum_required(VERSION 3.15)
project(sipfinder)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

find_package(Python REQUIRED COMPONENTS Development)
find_package(SIP REQUIRED)
