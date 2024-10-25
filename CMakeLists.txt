cmake_minimum_required(VERSION 3.10)
project(CMakeBoilerplateGenerator)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(CMakeBoilerplateGenerator src/main.cpp src/CMakeGenerator.cpp src/DependencyManager.cpp src/ConfigManager.cpp)
find_package(nlohmann_json REQUIRED)
target_link_libraries(CMakeBoilerplateGenerator nlohmann_json::nlohmann_json)

