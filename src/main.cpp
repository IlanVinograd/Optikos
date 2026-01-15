#include "platform/glfw/GLFWWindow.hpp"
#include "render/opengl/OpenGLRenderer.hpp"
#include <memory>

int main(void)
{
    Logger::add_logger();
    auto window = std::make_unique<Optikos::GLFWWindow>(800, 600, "App");
    window->setWindowTitleBar({25, 25, 25});
    while (!glfwWindowShouldClose(static_cast<GLFWwindow*>(window->native_handle()))) {
        // process_events();
        // render();

        glfwSwapBuffers(static_cast<GLFWwindow*>(window->native_handle()));
        glfwPollEvents();
    }
}