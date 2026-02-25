#include <memory>
#include <chrono>
#include <deque>
#include <string>

#include "optikos.hpp"
#include "optikos_config.hpp"
#include "utilities/logger.hpp"

int main()
{
    Logger::add_logger();
    Optikos::Optikos app = Optikos::Optikos("Optikos FPS Graph", 1400, 800);
    app.setWindowTitleBar(Optikos::Color{25, 25, 28});

    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-light.otf");
    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-Black.otf", "BOLD", 12.0);

    auto* topBar = app.addWidget(
        1, std::make_unique<Optikos::Container>(1400, 35, Optikos::Vec2{0, 0},
                                                Optikos::Color{20, 20, 22, 255}));
    topBar->setAutoExpand(Optikos::ExpandMode::Width);
    topBar->useVerticalLayout(false);
    topBar->setAlignment(Optikos::AlignMode::Left);
    topBar->setInterval(10);
    topBar->setOffset(15);

    auto titleLabel = std::make_unique<Optikos::Label>(
        "OPTIKOS GUI - FPS STRESS TEST", Optikos::Vec2{0, 0}, 350, 35);
    titleLabel->setFont("BOLD");
    titleLabel->setColor(Optikos::Color(100, 200, 255, 255));
    topBar->addSubWidget(std::move(titleLabel));

    auto fpsLabelPtr = std::make_unique<Optikos::Label>(
        "FPS: 0", Optikos::Vec2{0, 0}, 150, 35);
    fpsLabelPtr->setFont("BOLD");
    fpsLabelPtr->setColor(Optikos::Color(100, 255, 100, 255));
    auto* fpsLabel = topBar->addSubWidget(std::move(fpsLabelPtr));

    auto avgLabelPtr = std::make_unique<Optikos::Label>(
        "AVG: 0", Optikos::Vec2{0, 0}, 150, 35);
    avgLabelPtr->setColor(Optikos::Color(200, 200, 100, 255));
    auto* avgLabel = topBar->addSubWidget(std::move(avgLabelPtr));

    auto minLabelPtr = std::make_unique<Optikos::Label>(
        "MIN: 0", Optikos::Vec2{0, 0}, 150, 35);
    minLabelPtr->setColor(Optikos::Color(255, 100, 100, 255));
    auto* minLabel = topBar->addSubWidget(std::move(minLabelPtr));

    auto maxLabelPtr = std::make_unique<Optikos::Label>(
        "MAX: 0", Optikos::Vec2{0, 0}, 150, 35);
    maxLabelPtr->setColor(Optikos::Color(100, 255, 200, 255));
    auto* maxLabel = topBar->addSubWidget(std::move(maxLabelPtr));

    auto* graphBg = app.addWidget(
        2, std::make_unique<Optikos::Container>(1380, 400, Optikos::Vec2{10, 45},
                                                Optikos::Color{18, 18, 20, 255}));
    graphBg->setAutoExpand(Optikos::ExpandMode::Width);

    for (int i = 0; i <= 4; i++)
    {
        float y = 45.0f + (400.0f / 4.0f) * i;
        auto  gridLine = std::make_unique<Optikos::Container>(
            1380, 1, Optikos::Vec2{10, y}, Optikos::Color{40, 40, 45, 255});
        gridLine->setAutoExpand(Optikos::ExpandMode::Width);
        app.addWidget(10 + i, std::move(gridLine));
    }

    constexpr int   GRAPH_W        = 1380;
    constexpr int   GRAPH_H        = 390;
    constexpr int   BAR_W          = 3;
    constexpr int   BAR_GAP        = 1;
    constexpr int   MAX_BARS       = GRAPH_W / (BAR_W + BAR_GAP);
    constexpr float GRAPH_Y        = 50.0f;
    constexpr float GRAPH_BOTTOM_Y = GRAPH_Y + GRAPH_H;
    constexpr float TARGET_FPS     = 144.0f;

    struct Bar
    {
        Optikos::Container* widget = nullptr;
        uint32_t            id     = 0;
    };

    std::deque<Bar>  bars;
    std::deque<float> fpsHistory;
    uint32_t         nextBarId = 100;

    auto* stressContainer = app.addWidget(
        3, std::make_unique<Optikos::Container>(1380, 290, Optikos::Vec2{10, 460},
                                                Optikos::Color{22, 22, 25, 255}));
    stressContainer->setAutoExpand(Optikos::ExpandMode::Width);
    stressContainer->useVerticalLayout(false);
    stressContainer->setInterval(2);
    stressContainer->setOffset(5);

    auto stressTitle = std::make_unique<Optikos::Label>(
        "STRESS WIDGETS", Optikos::Vec2{0, 0}, 200, 25);
    stressTitle->setFont("BOLD");
    stressTitle->setColor(Optikos::Color(180, 180, 200));
    app.addWidget(4, std::move(stressTitle));

    auto* scrollStress = app.addWidget(
        5, std::make_unique<Optikos::ScrollContainer>(1380, 250, Optikos::Vec2{10, 490},
                                                      Optikos::Color{25, 25, 28, 255}));
    scrollStress->useVerticalLayout(false);
    scrollStress->setInterval(3);

    static const Optikos::Color btnColors[] = {
        {60, 120, 200, 255}, {80, 180, 100, 255}, {200, 100, 60, 255},
        {160, 80, 200, 255}, {200, 180, 60, 255}, {60, 180, 180, 255},
    };

    for (int i = 0; i < 300; i++)
    {
        auto btn = std::make_unique<Optikos::Button>(
            60, 240, Optikos::Vec2{0, 0},
            "W" + std::to_string(i));
        btn->setColor(btnColors[i % 6]);
        btn->setTextColor(Optikos::Color(230, 230, 230));
        scrollStress->addSubWidget(std::move(btn));
    }

    using clock     = std::chrono::high_resolution_clock;
    auto  lastFrame = clock::now();
    float minFps    = 99999.f;
    float maxFps    = 0.f;
    float avgFps    = 0.f;
    int   frameCount = 0;

    while (!app.should_close())
    {
        auto  now     = clock::now();
        float dt      = std::chrono::duration<float>(now - lastFrame).count();
        lastFrame     = now;
        float fps     = (dt > 0.0f) ? 1.0f / dt : 0.0f;

        fpsHistory.push_back(fps);
        if ((int)fpsHistory.size() > MAX_BARS)
            fpsHistory.pop_front();

        minFps = fps < minFps ? fps : minFps;
        maxFps = fps > maxFps ? fps : maxFps;
        frameCount++;
        avgFps += (fps - avgFps) / frameCount;
        if (frameCount > 10000) { frameCount = 1; avgFps = fps; }

        fpsLabel->setText("FPS: " + std::to_string((int)fps));
        avgLabel->setText("AVG: " + std::to_string((int)avgFps));
        minLabel->setText("MIN: " + std::to_string((int)minFps));
        maxLabel->setText("MAX: " + std::to_string((int)maxFps));

        if (fps >= 60.f)
            fpsLabel->setColor(Optikos::Color(100, 255, 100, 255));
        else if (fps >= 30.f)
            fpsLabel->setColor(Optikos::Color(255, 200, 50, 255));
        else
            fpsLabel->setColor(Optikos::Color(255, 80, 80, 255));

        float clampedFps = fps > TARGET_FPS ? TARGET_FPS : fps;
        float ratio      = clampedFps / TARGET_FPS;
        int   barH       = (int)(ratio * GRAPH_H);
        if (barH < 1) barH = 1;

        float barY = GRAPH_BOTTOM_Y - barH;
        float barX = 10.0f + (float)((int)fpsHistory.size() - 1) * (BAR_W + BAR_GAP);

        Optikos::Color barColor;
        if (fps >= 60.f)
            barColor = {50, 200, 80, 255};
        else if (fps >= 30.f)
            barColor = {220, 180, 40, 255};
        else
            barColor = {220, 60, 60, 255};

        auto bar = std::make_unique<Optikos::Container>(
            BAR_W, barH, Optikos::Vec2{barX, barY}, barColor);
        auto* barPtr = app.addWidget(nextBarId, std::move(bar));

        Bar b;
        b.widget = barPtr;
        b.id     = nextBarId++;
        bars.push_back(b);

        while ((int)bars.size() > MAX_BARS)
        {
            app.removeWidget(bars.front().id);
            bars.pop_front();
            for (int i = 0; i < (int)bars.size(); i++)
            {
                if (bars[i].widget)
                {
                    Optikos::Vec2 pos = bars[i].widget->getPosition();
                    pos.x   -= (BAR_W + BAR_GAP);
                    bars[i].widget->setPosition(pos);
                }
            }
        }

        app.begin();
        app.end();
    }
}