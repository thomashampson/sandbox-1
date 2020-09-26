cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)

project(processevents)

set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core Widgets Test REQUIRED)

set(SRCS
  main.cpp
  mainwindow.cpp
)

set(HEADERS
  mainwindow.h
)

add_executable(processEvents ${SRCS} ${HEADERS})
target_link_libraries(processEvents Qt5::Widgets)

# test
set(TEST_SRCS
  mainwindow.cpp
  test_mainwindow.cpp
)
set(TEST_HEADERS
  mainwindow.h
  test_mainwindow.h
)
add_executable(processEventsTest ${TEST_SRCS} ${TEST_HEADERS})
target_link_libraries(processEventsTest Qt5::Widgets Qt5::Test)
