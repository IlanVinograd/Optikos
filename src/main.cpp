#include <memory>

#include "input/glfw/GLFWInputSystem.hpp"
#include "optikos.hpp"
#include "platform/glfw/GLFWWindow.hpp"
#include "render/opengl/OpenGLRenderer.hpp"
#include "ui/UISystem.hpp"
#include "shader/GLSL/GLShader.hpp"
#include "ui/sdk/container.hpp"
#include "utilities/logger.hpp"
#include "utilities/vec.hpp"

int main()
{
    Logger::add_logger();

    Optikos::GraphicsConfig config{Optikos::GraphicsAPI::OpenGL, 6, 4};

    auto window   = std::make_unique<Optikos::GLFWWindow>(800, 600, "App", config);

    auto uiSystem = std::make_unique<UISystem>();
    auto shader = std::make_unique<GLShader>();
    uiSystem->add_widget(1, std::make_unique<Container>(400, 20, vec2{0,0}));
    auto renderer = std::make_unique<Optikos::OpenGLRenderer>(window.get(), std::move(uiSystem), std::move(shader));
    
    auto input = std::make_unique<Optikos::GLFWInputSystem>( window->native_handle());
    window->setInputSystem(input.get());

    Optikos::Optikos app(std::move(window), std::move(renderer), std::move(input), config);

    app.run();
}