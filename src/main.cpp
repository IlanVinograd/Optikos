#include "platform/glfw/GLFWWindow.hpp"
#include "render/opengl/OpenGLRenderer.hpp"
#include "platform/IWindow.hpp"
#include <memory>

int main(void)
{
    Logger::add_logger();

    Optikos::GraphicsConfig config{Optikos::GraphicsAPI::OpenGL, 4, 6};

    auto window = std::make_unique<Optikos::GLFWWindow>(800, 600, "App", config);
    auto render = std::make_unique<Optikos::OpenGLRenderer>(window.get());
    window->setWindowTitleBar({25, 25, 25});

    auto* nativeWin = static_cast<GLFWwindow*>(window->native_handle());
    while (!glfwWindowShouldClose(nativeWin)) {
        // process_events();
        // render();

        render->swap_buffer();
        window->poll_events();
    }
}