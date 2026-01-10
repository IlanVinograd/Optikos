cmake_minimum_required(VERSION 3.20)
project(Optikos LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(Optikos src/main.cpp)
target_link_libraries(Optikos PRIVATE glad::glad glfw)