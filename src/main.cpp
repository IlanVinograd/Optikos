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
    std::make_unique<Container>(800, 40, vec2{0,0}, Color{25.0, 25.0, 25.0, 255.0}));

    auto container2 = std::make_unique<Container>(30, 30, vec2{100,200}, Color{100.0, 125.0, 25.0, 255.0});
    container2->setClickable(true);

    container->addSubWidget(std::move(container2));

    auto container3 = std::make_unique<Container>(30, 30, vec2{100,200}, Color{2.0, 125.0, 225.0, 255.0});
    container->addSubWidget(std::move(container3));

    auto container4 = std::make_unique<Container>(30, 30, vec2{100,200}, Color{150.0, 1.0, 125.0, 255.0});
    container4->setClickable(true);
    container->addSubWidget(std::move(container4));

    container->setAutoExpand(1);
    container->setAlignment(0);
    container->setInterval(10);
    container->setOffset(10);
    
    //
    
    auto rec1 = std::make_unique<Container>(150, 40, vec2{0,100}, Color{255.0, 25.0, 25.0, 255.0});
    auto box1 = std::make_unique<Container>(30, 30, vec2{100,200}, Color{210.0, 135.0, 25.0, 255.0});
    rec1->setAlignment(1);
    rec1->addSubWidget(std::move(box1));

    auto rec2 = std::make_unique<Container>(150, 40, vec2{0,100}, Color{255.0, 25.0, 25.0, 255.0});
    auto box2 = std::make_unique<Container>(30, 30, vec2{100,200}, Color{100.0, 125.0, 25.0, 255.0});
    auto box3 = std::make_unique<Container>(30, 30, vec2{100,200}, Color{100.0, 125.0, 25.0, 255.0});
    Container* boxPtr2 = box2.get();
    rec2->setAlignment(1);
    rec2->setInterval(20);
    rec2->addSubWidget(std::move(box2));
    rec2->addSubWidget(std::move(box3));

    auto rec3 = std::make_unique<Container>(150, 40, vec2{0,100}, Color{255.0, 25.0, 25.0, 255.0});
    auto box4 = std::make_unique<Container>(30, 30, vec2{100,200}, Color{100.0, 125.0, 225.0, 255.0});
    auto box5 = std::make_unique<Container>(30, 30, vec2{100,200}, Color{100.0, 125.0, 225.0, 255.0});
    rec3->setAlignment(2);
    rec3->setInterval(20);
    rec3->addSubWidget(std::move(box4));
    rec3->addSubWidget(std::move(box5));

    auto* BigRec = uiSystem->add_widget(2, 
    std::make_unique<Container>(800, 40, vec2{0,100}, Color{25.0, 25.0, 255.0, 255.0}));
    BigRec->addSubWidget(std::move(rec1));
    BigRec->addSubWidget(std::move(rec2));
    BigRec->addSubWidget(std::move(rec3));

    BigRec->setAutoExpand(1);
    BigRec->setAlignment(1);
    BigRec->setInterval(120);
    
    boxPtr2->setClickable(true);
    //

    Optikos::Optikos app(
        std::move(window),
        std::move(renderer), 
        std::move(input),
        std::move(uiSystem),
        config
    );

    app.run();
}