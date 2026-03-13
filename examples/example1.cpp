#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>

#include <memory>
#include <iostream>

#include "optikos.hpp"

int main()
{
    /* init app */
    Optikos::Optikos app("Optikos", 800, 480);

    /* set custom color for title bar */
    app.setWindowTitleBar(Optikos::Color(255, 182, 193));

    /* Label */
    auto lbl = std::make_unique<Optikos::Label>("Hello Optikos!", Optikos::Vec2(20, 20));
    app.addWidget(1, std::move(lbl));

    /* Button */
    auto btn = std::make_unique<Optikos::Button>(120, 30, Optikos::Vec2(20, 60), "Click me");
    btn->setColor(Optikos::Color(40, 70, 90));
    btn->setEvent([]() { std::cout << "Button clicked!\n"; });
    app.addWidget(2, std::move(btn));

    /* TextBox */
    auto tb = std::make_unique<Optikos::TextBox>(200, 30, Optikos::Vec2(20, 110));
    tb->setText("Type here...");
    tb->setOnTextChanged([](const std::string& text) { std::cout << "Text: " << text << "\n"; });
    app.addWidget(3, std::move(tb));

    /* Slider (int) */
    static int sliderVal = 50;
    static int sliderMin = 0;
    static int sliderMax = 100;
    auto sldr = std::make_unique<Optikos::Slider>(200, 12, Optikos::Vec2(20, 160),
                                                  Optikos::OPTIKOS_INT, &sliderVal,
                                                  &sliderMin, &sliderMax);
    app.addWidget(4, std::move(sldr));

    /* Container with 2 buttons inside */
    auto cont = std::make_unique<Optikos::Container>(250, 60, Optikos::Vec2(20, 200),
                                                     Optikos::Color(30, 30, 60));
    cont->setAlignment(Optikos::AlignMode::Middle);
    cont->setInterval(10);
    cont->addSubWidget(std::make_unique<Optikos::Button>(80, 30, Optikos::Vec2(0, 0), "A"));
    cont->addSubWidget(std::make_unique<Optikos::Button>(80, 30, Optikos::Vec2(0, 0), "B"));
    app.addWidget(5, std::move(cont));

    /* ScrollContainer with labels */
    auto sc = std::make_unique<Optikos::ScrollContainer>(250, 100, Optikos::Vec2(20, 290),
                                                         Optikos::Color(20, 20, 40));
    sc->useVerticalLayout(true);
    sc->setAlignment(Optikos::AlignMode::Left);
    sc->setInterval(4);
    for (int i = 1; i <= 8; i++)
    {
        sc->addSubWidget(std::make_unique<Optikos::Label>(
            "Item " + std::to_string(i), Optikos::Vec2(0, 0), Optikos::Color(200, 200, 200)));
    }
    app.addWidget(6, std::move(sc));

    /* Image load via OpenGL/any other directly */
    int            w, h, ch;
    unsigned char* pixels = stbi_load("f35.jpg", &w, &h, &ch, 4);

    unsigned int texId = 0;
    if (pixels)
    {
        glGenTextures(1, &texId);
        glBindTexture(GL_TEXTURE_2D, texId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(pixels);

        auto img = std::make_unique<Optikos::Image>((Optikos::OpTextureID) texId, 350, 350,
                                                    Optikos::Vec2(300, 20));
        app.addWidget(7, std::move(img));
    }
    else
    {
        std::cerr << "Failed to load image: " << stbi_failure_reason() << "\n";
    }

    /* Render loop */
    while (!app.should_close())
    {
        app.begin();

        /* Your custom logic */

        app.end();
    }

    return 0;
}