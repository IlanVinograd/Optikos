#include <memory>

#include "optikos.hpp"
#include "optikos_config.hpp"
#include "utilities/logger.hpp"

int main()
{
    Logger::add_logger();
    Optikos::Optikos app = Optikos::Optikos("Optikos");
    app.setWindowTitleBar(Optikos::Color{25, 25, 25});

    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-light.otf");
    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-light.otf", "LIGHT", 30.0);
    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-Black.otf", "BOLD", 12.0);

    // auto* container = app.addWidget(
    //     1, std::make_unique<Container>(800, 35, Vec2{0, 0}, Color{25.0, 25.0, 25.0, 255.0}));

    // container->setAutoExpand(ExpandMode::Width);
    // container->setAlignment(AlignMode::Middle);
    // container->setInterval(12);
    // container->setOffset(15);

    // auto button1 = std::make_unique<Button>(40, 30, Vec2{10, 10});
    // container->addSubWidget(std::move(button1));

    // auto button2 = std::make_unique<Button>(40, 30, Vec2{10, 10}, "Move");
    // button2->setFont("BOLD");
    // auto* btn2Ptr = button2.get();
    // container->addSubWidget(std::move(button2));

    // auto button3 = std::make_unique<Button>(40, 30, Vec2{10, 10});
    // container->addSubWidget(std::move(button3));

    // auto* boxPtr = app.addWidget(
    //     2, std::make_unique<Container>(40, 40, Vec2{100, 100}, Color{100, 200, 100, 255.0}));

    // btn2Ptr->setEvent([boxPtr]() {
    //     boxPtr->setPosition(Vec2{boxPtr->getPosition().x + 15, boxPtr->getPosition().y});
    // });

    // auto* btn = app.addWidget(3, std::make_unique<Button>(140, 140, Vec2{200, 200}, "B O"));
    // btn->setFont("LIGHT");

    //

    auto* container =
        app.addWidget(1, std::make_unique<Optikos::Container>(500, 200, Optikos::Vec2{200, 200},
                                                              Optikos::Color{100, 50, 150, 255}));
    container->setAlignment(Optikos::AlignMode::Middle);

    Optikos::TextBox* createdBtn = nullptr;

    auto addBtn = std::make_unique<Optikos::Button>(60, 20, Optikos::Vec2{20, 20}, [&]() {
        auto btn = std::make_unique<Optikos::TextBox>(100, 35, Optikos::Vec2(100, 430));
        //btn->setText("New");
        createdBtn = container->addSubWidget(std::move(btn));
    });

    addBtn->setText("Add");
    addBtn->setFont("BOLD");
    addBtn->setColor(Optikos::Color(255,0,0,255));
    addBtn->setTextColor(Optikos::Color(0,255,0,255));
    
    auto changeTextBtn = std::make_unique<Optikos::Button>(100, 20, Optikos::Vec2{20, 50}, [&]() {
        if (createdBtn) {
            createdBtn->setText("Changed");
            createdBtn->setColor(Optikos::Color(255, 0, 0, 255));
            createdBtn->setTextColor(Optikos::Color(0, 255, 0, 255));
        }
    });

    changeTextBtn->setText("Change");

    app.addWidget(2, std::move(addBtn));
    app.addWidget(3, std::move(changeTextBtn));

    app.addWidget(4, std::make_unique<Optikos::Label>("TEXT CLICK HERE", Optikos::Vec2(300, 150), Optikos::Color(200, 100, 200, 255)));
    app.addWidget(5, std::make_unique<Optikos::Label>("TEXT CLICK HERE", Optikos::Vec2(100, 400), Optikos::Color(10, 130, 230, 255)));
    app.addWidget(6, std::make_unique<Optikos::Label>("TEXT CLICK HERE", Optikos::Vec2(150, 500), Optikos::Color(10, 250, 100, 255)));

    app.addWidget(7, std::make_unique<Optikos::TextBox>(100, 35, Optikos::Vec2(90, 430)));
    app.addWidget(8, std::make_unique<Optikos::TextBox>(100, 35, Optikos::Vec2(190, 430)));

    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-light.otf", "BOX", 48.0);
    auto textBox = std::make_unique<Optikos::TextBox>(200, 80, Optikos::Vec2(20, 70));
    textBox->setFont("BOX");
    app.addWidget(9, std::move(textBox));

    // auto* container = app.addWidget(1, std::make_unique<Container>(500,200, Vec2{200, 200},
    // Color{100,50,150,255})); auto btn1 = std::make_unique<Button>(60, 20, Vec2{20,20},
    // [container](){ container->addSubWidget(std::make_unique<Button>(50,50, Vec2{100,100})); });
    // btn1->setText("Add");
    // btn1->setFont("BOLD");
    // container->setAlignment(AlignMode::Middle);
    // container->setInterval(10);

    // app.addWidget(2, std::move(btn1));

    while (!app.should_close())
    {
        app.begin();

        app.end();
    }
}