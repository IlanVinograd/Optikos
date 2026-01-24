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

    auto uiSystem = std::make_unique<UISystem>();

    auto* container = uiSystem->add_widget(1, 
    std::make_unique<Container>(800, 60, vec2{0,0}, Color{125.0, 25.0, 25.0, 255.0}));

    container->setAutoExpand(1);

    auto* container2 = uiSystem->add_widget(2, 
        std::make_unique<Container>(800, 60, vec2{0,100}, Color{100.0, 25.0, 25.0, 255.0}));

    container->addSubWidget(container);

    Optikos::Optikos app(
        std::move(window),
        std::move(renderer), 
        std::move(input),
        std::move(uiSystem),
        config
    );

    app.run();
}