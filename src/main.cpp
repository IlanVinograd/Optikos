#include <memory>

// TODO: builder

#include "input/glfw/GLFWInputSystem.hpp"
#include "optikos.hpp"
#include "platform/glfw/GLFWWindow.hpp"
#include "render/opengl/OpenGLRenderer.hpp"
#include "shader/GLSL/GLShader.hpp"
#include "ui/UISystem.hpp"
#include "utilities/logger.hpp"

int main()
{
    Logger::add_logger();

    Optikos::GraphicsConfig config{Optikos::GraphicsAPI::OpenGL, 4, 6};
    auto                    window = std::make_unique<Optikos::GLFWWindow>(800, 600, "App", config);

    auto shader   = std::make_unique<GLShader>();
    auto renderer = std::make_unique<Optikos::OpenGLRenderer>(window.get(), std::move(shader));
    auto input = std::make_unique<Optikos::GLFWInputSystem>((GLFWwindow*) window->native_handle());
    auto uiSystem = std::make_unique<UISystem>();

    Optikos::Optikos app(std::move(window), std::move(renderer), std::move(input),
                         std::move(uiSystem), config);

    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-light.otf");
    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-light.otf", "LIGHT", 30.0);
    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-Black.otf", "BOLD", 12.0);

    auto* container = app.addWidget(
        1, std::make_unique<Container>(800, 35, vec2{0, 0}, Color{25.0, 25.0, 25.0, 255.0}));

    container->setAutoExpand(ExpandMode::Width);
    container->setAlignment(AlignMode::Middle);
    container->setInterval(12);
    container->setOffset(15);

    auto button1 = std::make_unique<Button>(40, 30, vec2{10, 10});
    container->addSubWidget(std::move(button1));

    auto button2 = std::make_unique<Button>(40, 30, vec2{10, 10}, "Move");
    button2->setFont("BOLD");
    auto* btn2Ptr = button2.get();
    container->addSubWidget(std::move(button2));

    auto button3 = std::make_unique<Button>(40, 30, vec2{10, 10});
    container->addSubWidget(std::move(button3));

    auto* boxPtr = app.addWidget(
        2, std::make_unique<Container>(40, 40, vec2{100, 100}, Color{100, 200, 100, 255.0}));

    btn2Ptr->setEvent([boxPtr]() {
        boxPtr->setPosition(vec2{boxPtr->getPosition().x + 15, boxPtr->getPosition().y});
    });

    auto* btn = app.addWidget(3, std::make_unique<Button>(140, 140, vec2{200, 200}, "B O"));
    btn->setFont("LIGHT");

    while (!app.should_close())
    {
        app.begin();

        app.end();
    }
}
