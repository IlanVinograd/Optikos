cmake_minimum_required(VERSION 3.20)
project(Optikos LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

set(COMMON_SOURCES
    src/main.cpp
    src/optikos.cpp
    src/utilities/logger.cpp
    src/render/opengl/OpenGLRenderer.cpp
    src/input/glfw/GLFWInputSystem.cpp
    src/ui/UISystem.cpp
    src/ui/sdk/container.cpp
    src/shader/GLSL/GLShader.cpp
)

add_executable(Optikos ${COMMON_SOURCES})

if (WIN32)
    set(WIN_SOURCES
        src/platform/glfw/GLFWWindow.cpp
    )
    target_sources(Optikos PRIVATE ${WIN_SOURCES})
    target_link_libraries(Optikos PRIVATE dwmapi)
    target_compile_definitions(Optikos PRIVATE PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
    set(LINUX_SOURCES
        src/platform/glfw/GLFWWindow.cpp
    )
    target_sources(Optikos PRIVATE ${LINUX_SOURCES})
    target_compile_definitions(Optikos PRIVATE PLATFORM_LINUX)
endif()

target_link_libraries(Optikos PRIVATE glad::glad glfw)

target_include_directories(Optikos PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

target_compile_options(Optikos PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Weffc++ -pedantic -pedantic-errors -Waggregate-return -Wcast-align -Wcast-qual -Wchar-subscripts -Wcomment -Wconversion -Wdisabled-optimization -Werror -Wfloat-equal -Wformat -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimplicit -Wimport -Winit-self -Winline -Winvalid-pch -Wunsafe-loop-optimizations -Wlong-long -Wmissing-braces -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wpadded -Wparentheses -Wpointer-arith -Wredundant-decls -Wreturn-type -Wsequence-point -Wshadow -Wsign-compare -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch -Wswitch-default -Wswitch-enum -Wtrigraphs -Wuninitialized -Wunknown-pragmas -Wunreachable-code -Wunused -Wunused-function -Wunused-label -Wunused-parameter -Wunused-value -Wunused-variable -Wvariadic-macros -Wvolatile-register-var -Wwrite-strings>
  $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Weffc++ -pedantic -pedantic-errors -Waggregate-return -Wcast-align -Wcast-qual -Wchar-subscripts -Wcomment -Wconversion -Wdisabled-optimization -Werror -Wfloat-equal -Wformat -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimplicit -Wimport -Winit-self -Winline -Winvalid-pch -Wunsafe-loop-optimizations -Wlong-long -Wmissing-braces -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wpadded -Wparentheses -Wpointer-arith -Wredundant-decls -Wreturn-type -Wsequence-point -Wshadow -Wsign-compare -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch -Wswitch-default -Wswitch-enum -Wtrigraphs -Wuninitialized -Wunknown-pragmas -Wunreachable-code -Wunused -Wunused-function -Wunused-label -Wunused-parameter -Wunused-value -Wunused-variable -Wvariadic-macros -Wvolatile-register-var -Wwrite-strings>
)