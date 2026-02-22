#include <memory>

#include "optikos.hpp"
#include "optikos_config.hpp"
#include "utilities/logger.hpp"

int main()
{
    Logger::add_logger();
    Optikos::Optikos app = Optikos::Optikos("Optikos GUI Showcase", 1400, 800);
    app.setWindowTitleBar(Optikos::Color{25, 25, 28});

    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-light.otf");
    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-Black.otf", "BOLD", 12.0);

    auto* topBar = app.addWidget(
        1, std::make_unique<Optikos::Container>(1400, 25, Optikos::Vec2{0, 0}, Optikos::Color{30, 30, 32, 255}));
    topBar->setAutoExpand(Optikos::ExpandMode::Width);
    topBar->setAlignment(Optikos::AlignMode::Left);
    topBar->setInterval(2);

    auto titleLabel = std::make_unique<Optikos::Label>(
        "OPTIKOS GUI SHOWCASE", Optikos::Vec2{0, 0}, 250, 25);
    titleLabel->setFont("BOLD");
    titleLabel->setColor(Optikos::Color(180, 200, 220, 255));
    topBar->addSubWidget(std::move(titleLabel));

    auto buttonDemo = std::make_unique<Optikos::Container>(
        200, 730, Optikos::Vec2{10, 40}, Optikos::Color{38, 38, 41, 255});
    buttonDemo->useVerticalLayout(true);
    buttonDemo->setAlignment(Optikos::AlignMode::Left);
    buttonDemo->setInterval(10);
    buttonDemo->setOffset(15);

    auto btnTitle = std::make_unique<Optikos::Label>(
        "BUTTONS", Optikos::Vec2{0, 0}, 150, 25);
    btnTitle->setFont("BOLD");
    btnTitle->setColor(Optikos::Color(180, 200, 220, 255));
    buttonDemo->addSubWidget(std::move(btnTitle));

    auto sep1 = std::make_unique<Optikos::Container>(
        170, 1, Optikos::Vec2{0, 0}, Optikos::Color{55, 55, 60, 255});
    buttonDemo->addSubWidget(std::move(sep1));

    auto normalBtn = std::make_unique<Optikos::Button>(170, 35, Optikos::Vec2{0, 0}, "Normal Button");
    normalBtn->setColor(Optikos::Color(55, 55, 60, 255));
    normalBtn->setTextColor(Optikos::Color(220, 220, 220));
    buttonDemo->addSubWidget(std::move(normalBtn));

    auto primaryBtn = std::make_unique<Optikos::Button>(170, 35, Optikos::Vec2{0, 0}, "Primary");
    primaryBtn->setColor(Optikos::Color(60, 100, 140, 255));
    primaryBtn->setTextColor(Optikos::Color(230, 230, 230));
    buttonDemo->addSubWidget(std::move(primaryBtn));

    auto successBtn = std::make_unique<Optikos::Button>(170, 35, Optikos::Vec2{0, 0}, "Success");
    successBtn->setColor(Optikos::Color(50, 120, 70, 255));
    successBtn->setTextColor(Optikos::Color(230, 230, 230));
    buttonDemo->addSubWidget(std::move(successBtn));

    auto warningBtn = std::make_unique<Optikos::Button>(170, 35, Optikos::Vec2{0, 0}, "Warning");
    warningBtn->setColor(Optikos::Color(140, 100, 40, 255));
    warningBtn->setTextColor(Optikos::Color(230, 230, 230));
    buttonDemo->addSubWidget(std::move(warningBtn));

    auto dangerBtn = std::make_unique<Optikos::Button>(170, 35, Optikos::Vec2{0, 0}, "Danger");
    dangerBtn->setColor(Optikos::Color(120, 50, 50, 255));
    dangerBtn->setTextColor(Optikos::Color(230, 230, 230));
    buttonDemo->addSubWidget(std::move(dangerBtn));

    auto sep2 = std::make_unique<Optikos::Container>(
        170, 1, Optikos::Vec2{0, 0}, Optikos::Color{55, 55, 60, 255});
    buttonDemo->addSubWidget(std::move(sep2));

    auto smallBtn = std::make_unique<Optikos::Button>(170, 25, Optikos::Vec2{0, 0}, "Small Button");
    smallBtn->setColor(Optikos::Color(55, 55, 60, 255));
    smallBtn->setTextColor(Optikos::Color(200, 200, 200));
    buttonDemo->addSubWidget(std::move(smallBtn));

    auto mediumBtn = std::make_unique<Optikos::Button>(170, 35, Optikos::Vec2{0, 0}, "Medium Button");
    mediumBtn->setColor(Optikos::Color(55, 55, 60, 255));
    mediumBtn->setTextColor(Optikos::Color(200, 200, 200));
    buttonDemo->addSubWidget(std::move(mediumBtn));

    auto largeBtn = std::make_unique<Optikos::Button>(170, 50, Optikos::Vec2{0, 0}, "Large Button");
    largeBtn->setColor(Optikos::Color(55, 55, 60, 255));
    largeBtn->setTextColor(Optikos::Color(200, 200, 200));
    buttonDemo->addSubWidget(std::move(largeBtn));

    auto sep3 = std::make_unique<Optikos::Container>(
        170, 1, Optikos::Vec2{0, 0}, Optikos::Color{55, 55, 60, 255});
    buttonDemo->addSubWidget(std::move(sep3));

    auto btnGroup = std::make_unique<Optikos::Container>(
        170, 35, Optikos::Vec2{0, 0}, Optikos::Color{38, 38, 41, 0});
    btnGroup->useVerticalLayout(false);
    btnGroup->setAlignment(Optikos::AlignMode::Left);
    btnGroup->setInterval(5);

    auto btn1 = std::make_unique<Optikos::Button>(52, 30, Optikos::Vec2{0, 0}, "One");
    btn1->setColor(Optikos::Color(50, 50, 55, 255));
    btn1->setTextColor(Optikos::Color(200, 200, 200));
    btnGroup->addSubWidget(std::move(btn1));

    auto btn2 = std::make_unique<Optikos::Button>(52, 30, Optikos::Vec2{0, 0}, "Two");
    btn2->setColor(Optikos::Color(50, 50, 55, 255));
    btn2->setTextColor(Optikos::Color(200, 200, 200));
    btnGroup->addSubWidget(std::move(btn2));

    auto btn3 = std::make_unique<Optikos::Button>(52, 30, Optikos::Vec2{0, 0}, "Three");
    btn3->setColor(Optikos::Color(50, 50, 55, 255));
    btn3->setTextColor(Optikos::Color(200, 200, 200));
    btnGroup->addSubWidget(std::move(btn3));

    buttonDemo->addSubWidget(std::move(btnGroup));

    app.addWidget(10, std::move(buttonDemo));

    auto sliderDemo = std::make_unique<Optikos::Container>(
        550, 270, Optikos::Vec2{220, 40}, Optikos::Color{40, 40, 43, 255});
    sliderDemo->useVerticalLayout(true);
    sliderDemo->setAlignment(Optikos::AlignMode::Left);
    sliderDemo->setInterval(12);
    sliderDemo->setOffset(20);

    auto sliderTitle = std::make_unique<Optikos::Label>(
        "SLIDERS & CONTROLS", Optikos::Vec2{0, 0}, 250, 25);
    sliderTitle->setFont("BOLD");
    sliderTitle->setColor(Optikos::Color(180, 200, 220, 255));
    sliderDemo->addSubWidget(std::move(sliderTitle));

    auto sep4 = std::make_unique<Optikos::Container>(
        510, 1, Optikos::Vec2{0, 0}, Optikos::Color{55, 55, 60, 255});
    sliderDemo->addSubWidget(std::move(sep4));

    auto volumeLabel = std::make_unique<Optikos::Label>(
        "Volume", Optikos::Vec2{0, 0}, 100, 18);
    volumeLabel->setColor(Optikos::Color(200, 200, 200));
    sliderDemo->addSubWidget(std::move(volumeLabel));

    float volume = 75.0f;
    float minVol = 0.0f;
    float maxVol = 100.0f;
    auto volumeSlider = std::make_unique<Optikos::Slider>(
        510, 20, Optikos::Vec2{0, 0}, 
        Optikos::OptikosType::OPTIKOS_FLOAT, &volume, &minVol, &maxVol);
    sliderDemo->addSubWidget(std::move(volumeSlider));

    auto brightnessLabel = std::make_unique<Optikos::Label>(
        "Brightness", Optikos::Vec2{0, 0}, 100, 18);
    brightnessLabel->setColor(Optikos::Color(200, 200, 200));
    sliderDemo->addSubWidget(std::move(brightnessLabel));

    float brightness = 50.0f;
    float minBright = 0.0f;
    float maxBright = 100.0f;
    auto brightnessSlider = std::make_unique<Optikos::Slider>(
        510, 20, Optikos::Vec2{0, 0},
        Optikos::OptikosType::OPTIKOS_FLOAT, &brightness, &minBright, &maxBright);
    sliderDemo->addSubWidget(std::move(brightnessSlider));

    auto speedLabel = std::make_unique<Optikos::Label>(
        "Speed", Optikos::Vec2{0, 0}, 100, 18);
    speedLabel->setColor(Optikos::Color(200, 200, 200));
    sliderDemo->addSubWidget(std::move(speedLabel));

    float speed = 1.5f;
    float minSpeed = 0.1f;
    float maxSpeed = 5.0f;
    auto speedSlider = std::make_unique<Optikos::Slider>(
        510, 20, Optikos::Vec2{0, 0},
        Optikos::OptikosType::OPTIKOS_FLOAT, &speed, &minSpeed, &maxSpeed);
    sliderDemo->addSubWidget(std::move(speedSlider));

    app.addWidget(11, std::move(sliderDemo));

    auto textDemo = std::make_unique<Optikos::Container>(
        550, 300, Optikos::Vec2{220, 320}, Optikos::Color{40, 40, 43, 255});
    textDemo->useVerticalLayout(true);
    textDemo->setAlignment(Optikos::AlignMode::Left);
    textDemo->setInterval(12);
    textDemo->setOffset(20);

    auto textTitle = std::make_unique<Optikos::Label>(
        "TEXT INPUTS", Optikos::Vec2{0, 0}, 250, 25);
    textTitle->setFont("BOLD");
    textTitle->setColor(Optikos::Color(180, 200, 220, 255));
    textDemo->addSubWidget(std::move(textTitle));

    auto sep5 = std::make_unique<Optikos::Container>(
        510, 1, Optikos::Vec2{0, 0}, Optikos::Color{55, 55, 60, 255});
    textDemo->addSubWidget(std::move(sep5));

    auto nameLabel = std::make_unique<Optikos::Label>(
        "Name", Optikos::Vec2{0, 0}, 100, 18);
    nameLabel->setColor(Optikos::Color(200, 200, 200));
    textDemo->addSubWidget(std::move(nameLabel));

    auto nameBox = std::make_unique<Optikos::TextBox>(510, 35, Optikos::Vec2{0, 0});
    textDemo->addSubWidget(std::move(nameBox));

    auto emailLabel = std::make_unique<Optikos::Label>(
        "Email", Optikos::Vec2{0, 0}, 100, 18);
    emailLabel->setColor(Optikos::Color(200, 200, 200));
    textDemo->addSubWidget(std::move(emailLabel));

    auto emailBox = std::make_unique<Optikos::TextBox>(510, 35, Optikos::Vec2{0, 0});
    textDemo->addSubWidget(std::move(emailBox));

    auto pathLabel = std::make_unique<Optikos::Label>(
        "File Path", Optikos::Vec2{0, 0}, 100, 18);
    pathLabel->setColor(Optikos::Color(200, 200, 200));
    textDemo->addSubWidget(std::move(pathLabel));

    auto pathBox = std::make_unique<Optikos::TextBox>(510, 35, Optikos::Vec2{0, 0});
    textDemo->addSubWidget(std::move(pathBox));

    app.addWidget(12, std::move(textDemo));

    auto layoutDemo = std::make_unique<Optikos::Container>(
        380, 600, Optikos::Vec2{780, 40}, Optikos::Color{38, 38, 41, 255});
    layoutDemo->useVerticalLayout(true);
    layoutDemo->setAlignment(Optikos::AlignMode::Left);
    layoutDemo->setInterval(15);
    layoutDemo->setOffset(20);

    auto layoutTitle = std::make_unique<Optikos::Label>(
        "LAYOUT EXAMPLES", Optikos::Vec2{0, 0}, 250, 25);
    layoutTitle->setFont("BOLD");
    layoutTitle->setColor(Optikos::Color(180, 200, 220, 255));
    layoutDemo->addSubWidget(std::move(layoutTitle));

    auto sep6 = std::make_unique<Optikos::Container>(
        340, 1, Optikos::Vec2{0, 0}, Optikos::Color{55, 55, 60, 255});
    layoutDemo->addSubWidget(std::move(sep6));

    auto horizLabel = std::make_unique<Optikos::Label>(
        "Horizontal Layout", Optikos::Vec2{0, 0}, 180, 20);
    horizLabel->setColor(Optikos::Color(180, 200, 220, 255));
    layoutDemo->addSubWidget(std::move(horizLabel));

    auto horizContainer = std::make_unique<Optikos::Container>(
        340, 40, Optikos::Vec2{0, 0}, Optikos::Color{45, 45, 48, 255});
    horizContainer->useVerticalLayout(false);
    horizContainer->setAlignment(Optikos::AlignMode::Middle);
    horizContainer->setInterval(8);

    auto h1 = std::make_unique<Optikos::Button>(75, 32, Optikos::Vec2{0, 0}, "Item 1");
    h1->setColor(Optikos::Color(60, 80, 100, 255));
    horizContainer->addSubWidget(std::move(h1));

    auto h2 = std::make_unique<Optikos::Button>(75, 32, Optikos::Vec2{0, 0}, "Item 2");
    h2->setColor(Optikos::Color(60, 80, 100, 255));
    horizContainer->addSubWidget(std::move(h2));

    auto h3 = std::make_unique<Optikos::Button>(75, 32, Optikos::Vec2{0, 0}, "Item 3");
    h3->setColor(Optikos::Color(60, 80, 100, 255));
    horizContainer->addSubWidget(std::move(h3));

    auto h4 = std::make_unique<Optikos::Button>(75, 32, Optikos::Vec2{0, 0}, "Item 4");
    h4->setColor(Optikos::Color(60, 80, 100, 255));
    horizContainer->addSubWidget(std::move(h4));

    layoutDemo->addSubWidget(std::move(horizContainer));

    auto vertLabel = std::make_unique<Optikos::Label>(
        "Vertical Layout (Left Align)", Optikos::Vec2{0, 0}, 250, 20);
    vertLabel->setColor(Optikos::Color(180, 200, 220, 255));
    layoutDemo->addSubWidget(std::move(vertLabel));

    auto vertContainer = std::make_unique<Optikos::Container>(
        340, 140, Optikos::Vec2{0, 0}, Optikos::Color{45, 45, 48, 255});
    vertContainer->useVerticalLayout(true);
    vertContainer->setAlignment(Optikos::AlignMode::Left);
    vertContainer->setInterval(6);
    vertContainer->setOffset(10);

    auto v1 = std::make_unique<Optikos::Button>(200, 28, Optikos::Vec2{0, 0}, "Option A");
    v1->setColor(Optikos::Color(80, 60, 100, 255));
    vertContainer->addSubWidget(std::move(v1));

    auto v2 = std::make_unique<Optikos::Button>(200, 28, Optikos::Vec2{0, 0}, "Option B");
    v2->setColor(Optikos::Color(80, 60, 100, 255));
    vertContainer->addSubWidget(std::move(v2));

    auto v3 = std::make_unique<Optikos::Button>(200, 28, Optikos::Vec2{0, 0}, "Option C");
    v3->setColor(Optikos::Color(80, 60, 100, 255));
    vertContainer->addSubWidget(std::move(v3));

    layoutDemo->addSubWidget(std::move(vertContainer));

    auto nestedLabel = std::make_unique<Optikos::Label>(
        "Nested Layouts", Optikos::Vec2{0, 0}, 180, 20);
    nestedLabel->setColor(Optikos::Color(180, 200, 220, 255));
    layoutDemo->addSubWidget(std::move(nestedLabel));

    auto nestedContainer = std::make_unique<Optikos::Container>(
        340, 120, Optikos::Vec2{0, 0}, Optikos::Color{45, 45, 48, 255});
    nestedContainer->useVerticalLayout(true);
    nestedContainer->setAlignment(Optikos::AlignMode::Middle);
    nestedContainer->setInterval(8);
    nestedContainer->setOffset(10);

    auto nestedRow1 = std::make_unique<Optikos::Container>(
        300, 32, Optikos::Vec2{0, 0}, Optikos::Color{45, 45, 48, 0});
    nestedRow1->useVerticalLayout(false);
    nestedRow1->setAlignment(Optikos::AlignMode::Left);
    nestedRow1->setInterval(6);

    auto n1 = std::make_unique<Optikos::Button>(95, 28, Optikos::Vec2{0, 0}, "A1");
    n1->setColor(Optikos::Color(100, 80, 60, 255));
    nestedRow1->addSubWidget(std::move(n1));

    auto n2 = std::make_unique<Optikos::Button>(95, 28, Optikos::Vec2{0, 0}, "A2");
    n2->setColor(Optikos::Color(100, 80, 60, 255));
    nestedRow1->addSubWidget(std::move(n2));

    auto n3 = std::make_unique<Optikos::Button>(95, 28, Optikos::Vec2{0, 0}, "A3");
    n3->setColor(Optikos::Color(100, 80, 60, 255));
    nestedRow1->addSubWidget(std::move(n3));

    nestedContainer->addSubWidget(std::move(nestedRow1));

    auto nestedRow2 = std::make_unique<Optikos::Container>(
        300, 32, Optikos::Vec2{0, 0}, Optikos::Color{45, 45, 48, 0});
    nestedRow2->useVerticalLayout(false);
    nestedRow2->setAlignment(Optikos::AlignMode::Left);
    nestedRow2->setInterval(6);

    auto n4 = std::make_unique<Optikos::Button>(95, 28, Optikos::Vec2{0, 0}, "B1");
    n4->setColor(Optikos::Color(100, 80, 60, 255));
    nestedRow2->addSubWidget(std::move(n4));

    auto n5 = std::make_unique<Optikos::Button>(95, 28, Optikos::Vec2{0, 0}, "B2");
    n5->setColor(Optikos::Color(100, 80, 60, 255));
    nestedRow2->addSubWidget(std::move(n5));

    auto n6 = std::make_unique<Optikos::Button>(95, 28, Optikos::Vec2{0, 0}, "B3");
    n6->setColor(Optikos::Color(100, 80, 60, 255));
    nestedRow2->addSubWidget(std::move(n6));

    nestedContainer->addSubWidget(std::move(nestedRow2));

    layoutDemo->addSubWidget(std::move(nestedContainer));

    app.addWidget(13, std::move(layoutDemo));

    auto statusBar = std::make_unique<Optikos::Container>(
        1400, 25, Optikos::Vec2{0, 775}, Optikos::Color{28, 28, 30, 255});
    statusBar->setAutoExpand(Optikos::ExpandMode::Width);
    statusBar->useVerticalLayout(false);
    statusBar->setAlignment(Optikos::AlignMode::Left);
    statusBar->setInterval(20);
    statusBar->setOffset(15);

    auto statusLabel = std::make_unique<Optikos::Label>(
        "Ready", Optikos::Vec2{0, 0}, 100, 20);
    statusLabel->setColor(Optikos::Color(150, 150, 150));
    statusBar->addSubWidget(std::move(statusLabel));

    auto infoLabel = std::make_unique<Optikos::Label>(
        "Optikos GUI v1.0", Optikos::Vec2{0, 0}, 150, 20);
    infoLabel->setColor(Optikos::Color(120, 120, 120));
    statusBar->addSubWidget(std::move(infoLabel));

    app.addWidget(20, std::move(statusBar));

    while (!app.should_close())
    {
        app.begin();
        app.end();
    }
}