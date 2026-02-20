#include <memory>

#include "optikos.hpp"
#include "optikos_config.hpp"
#include "utilities/logger.hpp"

int main()
{
    Logger::add_logger();
    Optikos::Optikos app = Optikos::Optikos("Optikos");
    app.setWindowTitleBar(Optikos::Color{20, 20, 20});

    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-light.otf");
    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-Black.otf", "BOLD", 12.0);

    auto* container = app.addWidget(
        1, std::make_unique<Optikos::Container>(800, 25, Optikos::Vec2{0, 0}, Optikos::Color{20, 20, 20, 255}));

    container->setAutoExpand(Optikos::ExpandMode::Width);
    container->setAlignment(Optikos::AlignMode::Left);
    container->setInterval(2);
    container->setOffset(30);

    auto button1 = std::make_unique<Optikos::Button>(35, 20, Optikos::Vec2{0, 0}, "File");
    button1->setColor(Optikos::Color(20, 20, 20));
    auto* btnPtr1 = container->addSubWidget(std::move(button1));

    auto button2 = std::make_unique<Optikos::Button>(35, 20, Optikos::Vec2{0, 0}, "Edit");
    button2->setColor(Optikos::Color(20, 20, 20));
    container->addSubWidget(std::move(button2));

    auto button3 = std::make_unique<Optikos::Button>(65, 20, Optikos::Vec2{0, 0}, "Render");
    button3->setColor(Optikos::Color(20, 20, 20));
    container->addSubWidget(std::move(button3));

    auto container2 = std::make_unique<Optikos::Container>(100, 100, Optikos::Vec2(30, 25), Optikos::Color(40, 40, 40));
    auto* cnBtn1 = container2->addSubWidget(std::make_unique<Optikos::Button>(60, 20, Optikos::Vec2{0, 0}, "Add"));
    cnBtn1->setColor(Optikos::Color(40, 40, 40));
    container2->setVisible(false);
    auto* cnPtr2 = app.addWidget(2, std::move(container2));

    btnPtr1->setEvent([&](){
        cnPtr2->setVisible(!cnPtr2->getVisible());
    });

    auto* labelPtr = app.addWidget(3, std::make_unique<Optikos::Label>("", Optikos::Vec2(60, 100), 280, 20));
    auto* textBoxPtr = app.addWidget(4, std::make_unique<Optikos::TextBox>(200, 30, Optikos::Vec2(180, 180)));

    textBoxPtr->setOnTextChanged([labelPtr](const std::string& newText) {
        labelPtr->setText(newText);
    });

    //

    // auto* container =
    //     app.addWidget(1, std::make_unique<Optikos::Container>(500, 200, Optikos::Vec2{200, 200},
    //                                                           Optikos::Color{100, 50, 150, 255}));
    // container->setAlignment(Optikos::AlignMode::Middle);

    // Optikos::TextBox* createdBtn = nullptr;

    // auto addBtn = std::make_unique<Optikos::Button>(60, 20, Optikos::Vec2{20, 20}, [&]() {
    //     auto btn = std::make_unique<Optikos::TextBox>(100, 35, Optikos::Vec2(100, 430));
    //     //btn->setText("New");
    //     createdBtn = container->addSubWidget(std::move(btn));
    // });

    // auto btn3 = std::make_unique<Optikos::Button>(60, 20, Optikos::Vec2{20, 60}, [&]() {
    //     auto bt = std::make_unique<Optikos::Button>(100, 35, Optikos::Vec2(100, 430), "ABC");
    //     //bt->setText("ABC");
    //     container->addSubWidget(std::move(bt));
    // });

    // btn3->setText("btn");
    // app.addWidget(7, std::move(btn3));

    // addBtn->setText("Add");
    // addBtn->setFont("LIGHT");
    // addBtn->setColor(Optikos::Color(255,0,0,255));
    // addBtn->setTextColor(Optikos::Color(0,255,0,255));
    
    // auto changeTextBtn = std::make_unique<Optikos::Button>(100, 20, Optikos::Vec2{20, 50}, [&]() {
    //     if (createdBtn) {
    //         createdBtn->setText("Changed");
    //         createdBtn->setColor(Optikos::Color(255, 0, 0, 255));
    //         createdBtn->setTextColor(Optikos::Color(0, 255, 0, 255));
    //     }
    // });

    // changeTextBtn->setText("Change");

    // app.addWidget(2, std::move(addBtn));
    // app.addWidget(3, std::move(changeTextBtn));

    // app.addWidget(4, std::make_unique<Optikos::Label>("TEXT CLICK HERE", Optikos::Vec2(300, 150), Optikos::Color(200, 100, 200, 255)));
    // app.addWidget(5, std::make_unique<Optikos::Label>("TEXT CLICK HERE", Optikos::Vec2(100, 400), Optikos::Color(10, 130, 230, 255)));
    // app.addWidget(6, std::make_unique<Optikos::Label>("TEXT CLICK HERE", Optikos::Vec2(150, 500), Optikos::Color(10, 250, 100, 255)));

    while (!app.should_close())
    {
        app.begin();

        
        app.end();
    }
}