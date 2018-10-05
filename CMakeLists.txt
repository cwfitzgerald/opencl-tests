cmake_minimum_required(VERSION 3.12)

project(opencltests LANGUAGES CXX)

find_package(OpenCL 1.2 REQUIRED)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/simple/*.cpp")
file(GLOB_RECURSE HEADERS LIST_DIRECTORIES false CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/simple/*.hpp")
file(GLOB_RECURSE OPENCL LIST_DIRECTORIES false CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/simple/*.cl")

configure_file(config.hpp.in config.hpp)

add_executable(simple ${SOURCES} ${HEADERS} config.hpp ${OPENCL})
target_include_directories(simple PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(simple PRIVATE OpenCL::OpenCL)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS} ${OPENCL})
