# C++ library
add_library(widgets SHARED InfoWidget.cpp)
target_link_libraries(widgets Qt5::Widgets)
set_property(
  TARGET widgets PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                          ${CMAKE_CURRENT_LIST_DIR}
)

# Python bindings
add_subdirectory(bindings/pylib)
