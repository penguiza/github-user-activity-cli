cmake_minimum_required(VERSION 3.15)
project(user-activity-cli)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find packages installed by vcpkg
find_package(cpr REQUIRED)
find_package(nlohmann_json REQUIRED)

# Add executable from the src directory
add_executable(user-activity-cli src/main.cpp)

# Link libraries
target_link_libraries(user-activity-cli PRIVATE cpr::cpr nlohmann_json::nlohmann_json)
