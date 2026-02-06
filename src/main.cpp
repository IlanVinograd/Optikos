#include "optikos_config.hpp"
#include "optikos.hpp"

#include "utilities/logger.hpp"

#include <memory>

int main()
{
    Logger::add_logger();
    Optikos::Optikos app("Optikos");
    app.setWindowTitleBar(Optikos::Color{25,25,25});

    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-light.otf");
    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-light.otf", "LIGHT", 30.0);
    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-Black.otf", "BOLD", 12.0);

    // auto* container = app.addWidget(
    //     1, std::make_unique<Container>(800, 35, vec2{0, 0}, Color{25.0, 25.0, 25.0, 255.0}));

    // container->setAutoExpand(ExpandMode::Width);
    // container->setAlignment(AlignMode::Middle);
    // container->setInterval(12);
    // container->setOffset(15);

    // auto button1 = std::make_unique<Button>(40, 30, vec2{10, 10});
    // container->addSubWidget(std::move(button1));

    // auto button2 = std::make_unique<Button>(40, 30, vec2{10, 10}, "Move");
    // button2->setFont("BOLD");
    // auto* btn2Ptr = button2.get();
    // container->addSubWidget(std::move(button2));

    // auto button3 = std::make_unique<Button>(40, 30, vec2{10, 10});
    // container->addSubWidget(std::move(button3));

    // auto* boxPtr = app.addWidget(
    //     2, std::make_unique<Container>(40, 40, vec2{100, 100}, Color{100, 200, 100, 255.0}));

    // btn2Ptr->setEvent([boxPtr]() {
    //     boxPtr->setPosition(vec2{boxPtr->getPosition().x + 15, boxPtr->getPosition().y});
    // });

    // auto* btn = app.addWidget(3, std::make_unique<Button>(140, 140, vec2{200, 200}, "B O"));
    // btn->setFont("LIGHT");

    auto* container = app.addWidget(1, std::make_unique<Container>(500,200, vec2{200, 200}, Color{100,50,150,255}));
    auto btn1 = std::make_unique<Button>(60, 20, vec2{20,20}, [container](){ container->addSubWidget(std::make_unique<Button>(50,50, vec2{100,100})); });
    btn1->setText("Add");
    btn1->setFont("BOLD");
    container->setAlignment(AlignMode::Middle);
    container->setInterval(10);

    app.addWidget(2, std::move(btn1));

    while (!app.should_close())
    {
        app.begin();

        app.end();
    }
}