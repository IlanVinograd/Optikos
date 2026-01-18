#include <memory>

#include "input/glfw/GLFWInputSystem.hpp"
#include "optikos.hpp"
#include "platform/glfw/GLFWWindow.hpp"
#include "render/opengl/OpenGLRenderer.hpp"
#include "ui/UISystem.hpp"
#include "utilities/logger.hpp"

int main()
{
    Logger::add_logger();

    Optikos::GraphicsConfig config{Optikos::GraphicsAPI::OpenGL, 4, 6};

    auto window   = std::make_unique<Optikos::GLFWWindow>(800, 600, "App", config);
    auto uiSystem = std::make_unique<UISystem>();
    auto renderer = std::make_unique<Optikos::OpenGLRenderer>(window.get(), uiSystem.get());
    window->setRenderer(renderer.get());
    auto input = std::make_unique<Optikos::GLFWInputSystem>((GLFWwindow*) window->native_handle());

    Optikos::Optikos app(std::move(window), std::move(renderer), std::move(input), config);
    app.run();
}