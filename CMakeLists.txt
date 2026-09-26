cmake_minimum_required(VERSION 3.25)

# main
project(raytracer)

# setting c++ version
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# exporting compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# packages
find_package(stb CONFIG REQUIRED)

# finalization
file(GLOB_RECURSE CPP_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/dev/src/*.cpp")
add_executable(${PROJECT_NAME} ${CPP_SOURCES})

target_compile_definitions(${PROJECT_NAME} PUBLIC RTOUT="${CMAKE_CURRENT_SOURCE_DIR}/rtout/")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/dev/include/")
target_link_libraries(${PROJECT_NAME} PUBLIC stb::stb)