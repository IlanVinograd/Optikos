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

    Optikos::GraphicsConfig config{Optikos::GraphicsAPI::OpenGL, 4, 6};
    auto window = std::make_unique<Optikos::GLFWWindow>(800, 600, "App", config);

    auto shader = std::make_unique<GLShader>();
    auto renderer = std::make_unique<Optikos::OpenGLRenderer>(
        window.get(), 
        std::move(shader)
    );
    
    auto input = std::make_unique<Optikos::GLFWInputSystem>(
        (GLFWwindow*)window->native_handle()
    );
    window->setInputSystem(input.get());

    auto uiSystem = std::make_unique<UISystem>();

    uiSystem->add_widget(1, std::make_unique<Container>(800, 60, vec2{0,0}, Color{25.0, 25.0, 25.0, 255.0}));
    uiSystem->add_widget(2, std::make_unique<Container>(800, 60, vec2{0,40}, Color{1.0, 1.0, 100.0, 255.0}));
    uiSystem->add_widget(3, std::make_unique<Container>(800, 60, vec2{0,100}, Color{1.0, 100.0, 1.0, 255.0}));
    uiSystem->add_widget(4, std::make_unique<Container>(800, 60, vec2{0,200}, Color{100.0, 1.0, 1.0, 255.0}));

    Optikos::Optikos app(
        std::move(window), 
        std::move(renderer), 
        std::move(input),
        std::move(uiSystem),
        config
    );

    app.run();
}