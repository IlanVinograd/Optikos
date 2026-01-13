#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef PLATFORM_WINDOWS
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#endif

#include <glad/glad.h>
#include <platform/titlebar.hpp>
#include <iostream>
#include <utilities/logger.hpp>

static void error_callback([[maybe_unused]]int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key,[[maybe_unused]] int scancode, int action,[[maybe_unused]] int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    Logger logger;
    logger.add_logger("log");
    logger.log("Logger named: log initialized", Logger::Severity::trace);
    
    glfwSetErrorCallback(error_callback);
 
    if (!glfwInit())
        exit(EXIT_FAILURE);
 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
    GLFWwindow* window = glfwCreateWindow(640, 480, "Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    logger.log("Window opened", Logger::Severity::trace);

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    #ifdef PLATFORM_WINDOWS
        HWND hwnd = glfwGetWin32Window(window);
        set_title_bar(hwnd, UIColors::TitleBar);
    #else
        set_title_bar(window, UIColors::TitleBar);
    #endif

    gladLoadGL();

    while (!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    logger.log("Window closed", Logger::Severity::trace);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}