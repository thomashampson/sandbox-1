cmake_minimum_required(VERSION 3.1)
project(singleton)

set ( LIB_SRCS
  Foo.cpp
)

set ( LIB_HEADERS
  Foo.h
)

set ( EXE_SRCS
  main.cpp
)

add_compile_options(-Wall -Wextra -fvisibility=hidden)

add_library(foo SHARED ${LIB_SRCS} ${LIB_HEADERS})
#set_target_properties(foo PROPERTIES COMPILE_DEFINITIONS foo_Exports)

add_executable(singleton ${EXE_SRCS})
target_link_libraries(singleton foo)
