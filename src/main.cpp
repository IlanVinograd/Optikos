#include <memory>

#include "input/glfw/GLFWInputSystem.hpp"
#include "optikos.hpp"
#include "platform/glfw/GLFWWindow.hpp"
#include "render/opengl/OpenGLRenderer.hpp"
#include "ui/UISystem.hpp"
#include "shader/GLSL/GLShader.hpp"
#include "ui/sdk/container.hpp"
#include "ui/sdk/button.hpp"
#include "utilities/logger.hpp"
#include "utilities/vec.hpp"

void setFont(Optikos::IRenderer* renderer, std::string_view path ,std::string fontName = DEFAULT0_FONT, float fontSize = DEFAULT0_FONTSIZE) {
    auto& font = TextFont::getInstance();
    font.loadFont(path, fontName, fontSize);
    unsigned int id = renderer->loadTexture(font.getAtlasData(fontName), font.getAtlasSize(fontName), font.getAtlasSize(fontName));
    font.setAtlasTextureId(id, fontName);
}

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

    // i run like Optikos::pushFont(font, fontName or will be set as deafult); and this run this
    // start
    setFont(renderer.get(), "C:/Users/ilanv/Optikos/res/fonts/Titillium-light.otf");
    setFont(renderer.get(), "C:/Users/ilanv/Optikos/res/fonts/Titillium-light.otf", "LIGHT", 30.0);
    setFont(renderer.get(), "C:/Users/ilanv/Optikos/res/fonts/Titillium-Black.otf", "BOLD", 12.0);
    // end

    auto* container = uiSystem->add_widget(1, 
    std::make_unique<Container>(800, 35, vec2{0,0}, Color{25.0, 25.0, 25.0, 255.0}));

    auto button1 = std::make_unique<Button>(40, 30, vec2{10,10});

    container->addSubWidget(std::move(button1));

    auto button2 = std::make_unique<Button>(40, 30, vec2{10,10}, "Move");
    button2->setFont("BOLD");
    auto* btn2Ptr = button2.get();
    container->addSubWidget(std::move(button2));

    auto button3 = std::make_unique<Button>(40, 30, vec2{10,10});
    container->addSubWidget(std::move(button3));

    auto* boxPtr = uiSystem->add_widget(2, std::make_unique<Container>(40, 40, vec2{100,100}, Color{100,200,100, 255.0}));
    btn2Ptr->setEvent([&](){ boxPtr->setPosition(vec2{boxPtr->getPosition().x+15, boxPtr->getPosition().y}); });
    container->setAutoExpand(ExpandMode::Width);
    container->setAlignment(AlignMode::Middle);
    container->setInterval(12);
    container->setOffset(15);
    
    auto btn = std::make_unique<Button>(140, 140, vec2(200, 200), "B O");
    btn->setFont("LIGHT");
    uiSystem->add_widget(3, std::move(btn));

    //
    
    // auto rec1 = std::make_unique<Container>(150, 40, vec2{0,100}, Color{255.0, 25.0, 25.0, 255.0});
    // //auto box1 = std::make_unique<Container>(30, 30, vec2{100,200}, Color{210.0, 135.0, 25.0, 255.0});
    // auto button = std::make_unique<Button>(20, 20, vec2{10,10}, "CLICK", Color{50,255,255,255.0}, []() {std::cout << "CLICK" << std::endl;});
    // rec1->setAlignment(1);
    // rec1->addSubWidget(std::move(button));

    // auto rec2 = std::make_unique<Container>(150, 40, vec2{0,100}, Color{255.0, 25.0, 25.0, 255.0});
    // auto box2 = std::make_unique<Container>(30, 30, vec2{100,200}, Color{100.0, 125.0, 25.0, 255.0});
    // auto box3 = std::make_unique<Container>(30, 30, vec2{100,200}, Color{100.0, 125.0, 25.0, 255.0});
    // Container* boxPtr2 = box2.get();
    // rec2->setAlignment(1);
    // rec2->setInterval(20);
    // rec2->addSubWidget(std::move(box2));
    // rec2->addSubWidget(std::move(box3));

    // auto rec3 = std::make_unique<Container>(150, 40, vec2{0,100}, Color{255.0, 25.0, 25.0, 255.0});
    // auto box4 = std::make_unique<Container>(30, 30, vec2{100,200}, Color{100.0, 125.0, 225.0, 255.0});
    // auto box5 = std::make_unique<Container>(30, 30, vec2{100,200}, Color{100.0, 125.0, 225.0, 255.0});
    // rec3->setAlignment(2);
    // rec3->setInterval(20);
    // rec3->addSubWidget(std::move(box4));
    // rec3->addSubWidget(std::move(box5));

    // auto* BigRec = uiSystem->add_widget(2, 
    // std::make_unique<Container>(800, 40, vec2{0,100}, Color{25.0, 25.0, 255.0, 255.0}));
    // BigRec->addSubWidget(std::move(rec1));
    // BigRec->addSubWidget(std::move(rec2));
    // BigRec->addSubWidget(std::move(rec3));

    // BigRec->setAutoExpand(1);
    // BigRec->setAlignment(1);
    // BigRec->setInterval(120);
    
    // boxPtr2->setClickable(true);

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