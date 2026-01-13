cmake_minimum_required(VERSION 3.20)
project(Optikos LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

file(GLOB_RECURSE UTILITY_SOURCES 
    CONFIGURE_DEPENDS
    "src/utilities/*.cpp"
)

set(COMMON_SOURCES
    src/main.cpp
    ${UTILITY_SOURCES}
)

set(WIN_SOURCES
    src/platform/windows/win_titlebar.cpp
)

set(LINUX_SOURCES
    src/platform/linux/linux_titlebar.cpp
)

add_executable(Optikos ${COMMON_SOURCES})

if (WIN32)
    target_sources(Optikos PRIVATE ${WIN_SOURCES})
    target_link_libraries(Optikos PRIVATE dwmapi)
    target_compile_definitions(Optikos PRIVATE PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
    target_sources(Optikos PRIVATE ${LINUX_SOURCES})
    target_compile_definitions(Optikos PRIVATE PLATFORM_LINUX)
endif()

target_link_libraries(Optikos PRIVATE glad::glad glfw)

target_include_directories(Optikos PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_compile_options(Optikos PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)