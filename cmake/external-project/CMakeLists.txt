###############################################################################
# Testing an external project
###############################################################################
cmake_minimum_required( VERSION 2.8.12 )

project( ExternalAssets )

set( THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty_binaries )

include ( ExternalProject )
ExternalProject_Add( thirdparty 
                     PREFIX ${THIRD_PARTY_DIR}
                     GIT_REPOSITORY "https://github.com/martyngigg/scripts.git"
                     GIT_TAG master
                     CONFIGURE_COMMAND ""
                     BUILD_COMMAND ""
                     INSTALL_COMMAND ""
                     TEST_COMMAND ""
)

set( SRCS src/main.cpp )

add_executable ( main ${SRCS} )
add_dependencies ( main thirdparty )