#include <chrono>
#include <cmath>
#include <deque>
#include <memory>
#include <string>
#include <vector>

#include "optikos.hpp"
#include "optikos_config.hpp"
#include "utilities/logger.hpp"

constexpr int   WIN_W     = 1300;
constexpr int   WIN_H     = 800;
constexpr int   TOPBAR_H  = 40;
constexpr int   SIDEBAR_W = 200;
constexpr float MAIN_X    = (float) SIDEBAR_W + 30.0f;
constexpr float MAIN_W    = (float) (WIN_W - SIDEBAR_W - 20);

constexpr int   GRAPH_COUNT = 3;
constexpr float GRAPH_H     = 185.0f;
constexpr float GRAPH_GAP   = 8.0f;
constexpr float GRAPHS_Y    = (float) TOPBAR_H + 8.0f;

constexpr int MAX_PLOT_PTS = 1000;

constexpr Optikos::Color COL_PANEL     = {22, 22, 26, 255};
constexpr Optikos::Color COL_PANEL2    = {28, 28, 33, 255};
constexpr Optikos::Color COL_BG        = {14, 14, 18, 255};
constexpr Optikos::Color COL_GRID      = {35, 35, 42, 255};
constexpr Optikos::Color COL_TEXT      = {200, 200, 210, 255};
constexpr Optikos::Color COL_TEXT_DIM  = {100, 100, 115, 255};
constexpr Optikos::Color COL_SEPARATOR = {40, 40, 48, 255};
constexpr Optikos::Color COL_SIN       = {50, 200, 100, 255};
constexpr Optikos::Color COL_COS       = {60, 140, 255, 255};
constexpr Optikos::Color COL_TAN       = {230, 100, 60, 255};
constexpr Optikos::Color COL_ZERO      = {55, 55, 65, 255};

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

GLuint loadTexture(const char* filename, int* out_width, int* out_height)
{
    int            channels;
    unsigned char* data = stbi_load(filename, out_width, out_height, &channels, 4);
    if (!data) return 0;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, *out_width, *out_height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 data);
    stbi_image_free(data);
    return tex;
}

int main()
{
    Logger::add_logger();
    Optikos::Optikos app("Optikos — Graphs", WIN_W, WIN_H);
    app.setWindowTitleBar(Optikos::Color{12, 12, 15});

    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-light.otf");
    app.pushFont("C:/Users/ilanv/Optikos/res/fonts/Titillium-Black.otf", "BOLD", 12.0);

    int    imgW, imgH;
    int    w, h;
    GLuint tex  = loadTexture("C:/Users/ilanv/Optikos/res/images/image.png", &imgW, &imgH);
    GLuint tex2 = loadTexture("C:/Users/ilanv/Optikos/res/images/image2.jpg", &w, &h);
    auto*  img  = app.addWidget(
        1000000, std::make_unique<Optikos::Image>(tex, imgW, imgH, Optikos::Vec2(700, 700)));

    auto mkLabel =
        [](const std::string& t, int w, int h, Optikos::Color c = COL_TEXT, bool bold = false)
    {
        auto l = std::make_unique<Optikos::Label>(t, Optikos::Vec2{0, 0}, w, h, c);
        if (bold) l->setFont("BOLD");
        return l;
    };

    auto mkSep = [](int w)
    { return std::make_unique<Optikos::Container>(w, 1, Optikos::Vec2{0, 0}, COL_SEPARATOR); };

    auto* topBar = app.addWidget(
        1, std::make_unique<Optikos::Container>(WIN_W, TOPBAR_H, Optikos::Vec2{0, 0}, COL_PANEL));
    topBar->setAutoExpand(Optikos::ExpandMode::Width);
    topBar->useVerticalLayout(false);
    topBar->setAlignment(Optikos::AlignMode::Left);
    topBar->setInterval(10);
    topBar->setOffset(14);

    topBar->addSubWidget(mkLabel("  OPTIKOS", 120, TOPBAR_H / 2, {60, 140, 255, 255}, true));
    topBar->addSubWidget(
        std::make_unique<Optikos::Container>(1, TOPBAR_H - 10, Optikos::Vec2{0, 0}, COL_SEPARATOR));
    topBar->addSubWidget(mkLabel("sin(x)", 80, TOPBAR_H / 2, COL_SIN, true));
    topBar->addSubWidget(mkLabel("cos(x)", 80, TOPBAR_H / 2, COL_COS, true));
    topBar->addSubWidget(mkLabel("tan(x)", 80, TOPBAR_H / 2, COL_TAN, true));
    topBar->addSubWidget(
        std::make_unique<Optikos::Container>(1, TOPBAR_H - 10, Optikos::Vec2{0, 0}, COL_SEPARATOR));
    auto* timeLabel = topBar->addSubWidget(mkLabel("t = 0.00", 160, TOPBAR_H / 2, COL_TEXT_DIM));

    auto* sidebar = app.addWidget(
        2, std::make_unique<Optikos::Container>(
               SIDEBAR_W, WIN_H - TOPBAR_H, Optikos::Vec2{0, (float) TOPBAR_H + 10}, COL_PANEL));
    sidebar->useVerticalLayout(true);
    sidebar->setAlignment(Optikos::AlignMode::Left);
    sidebar->setInterval(5);
    sidebar->setOffset(10);

    sidebar->addSubWidget(mkLabel("CONTROLS", SIDEBAR_W - 20, 26, {60, 140, 255, 255}, true));
    sidebar->addSubWidget(mkSep(SIDEBAR_W - 20));

    bool  paused   = false;
    float speed    = 1.0f;
    float freq     = 1.0f;
    float ampSin   = 1.0f;
    float ampCos   = 1.0f;
    float ampTan   = 1.0f;
    float plotPtsF = 550.0f;

    auto btnP = std::make_unique<Optikos::Button>(SIDEBAR_W - 20, 32, Optikos::Vec2{0, 0}, "Pause");
    btnP->setColor({50, 50, 60, 255});
    btnP->setTextColor(COL_TEXT);
    auto* btnPPtr = sidebar->addSubWidget(std::move(btnP));
    bool  swap    = false;
    btnPPtr->setEvent(
        [&]()
        {
            paused = !paused;
            btnPPtr->setText(paused ? "Resume" : "Pause");
            btnPPtr->setColor(paused ? Optikos::Color{80, 50, 50, 255}
                                     : Optikos::Color{50, 50, 60, 255});

            // custom event
            if (swap)
            {
                img->setTexture(tex2);
                img->resize(w, h);
            }
            else
            {
                img->setTexture(tex);
                img->resize(imgW, imgH);
            }
            swap = !swap;
            //
        });

    sidebar->addSubWidget(mkSep(SIDEBAR_W - 20));
    sidebar->addSubWidget(mkLabel("SPEED", SIDEBAR_W - 20, 20, COL_TEXT_DIM));
    float speedMin = 0.1f, speedMax = 5.0f;
    sidebar->addSubWidget(std::make_unique<Optikos::Slider>(SIDEBAR_W - 20, 18, Optikos::Vec2{0, 0},
                                                            Optikos::OPTIKOS_FLOAT, &speed,
                                                            &speedMin, &speedMax));

    sidebar->addSubWidget(mkLabel("FREQUENCY", SIDEBAR_W - 20, 20, COL_TEXT_DIM));
    float freqMin = 0.2f, freqMax = 4.0f;
    sidebar->addSubWidget(std::make_unique<Optikos::Slider>(SIDEBAR_W - 20, 18, Optikos::Vec2{0, 0},
                                                            Optikos::OPTIKOS_FLOAT, &freq, &freqMin,
                                                            &freqMax));

    sidebar->addSubWidget(mkSep(SIDEBAR_W - 20));
    sidebar->addSubWidget(mkLabel("SIN AMP", SIDEBAR_W - 20, 20, COL_SIN));
    float aMin = 0.1f, aMax = 1.0f;
    sidebar->addSubWidget(std::make_unique<Optikos::Slider>(
        SIDEBAR_W - 20, 18, Optikos::Vec2{0, 0}, Optikos::OPTIKOS_FLOAT, &ampSin, &aMin, &aMax));

    sidebar->addSubWidget(mkLabel("COS AMP", SIDEBAR_W - 20, 20, COL_COS));
    float aMin2 = 0.1f, aMax2 = 1.0f;
    sidebar->addSubWidget(std::make_unique<Optikos::Slider>(
        SIDEBAR_W - 20, 18, Optikos::Vec2{0, 0}, Optikos::OPTIKOS_FLOAT, &ampCos, &aMin2, &aMax2));

    sidebar->addSubWidget(mkLabel("TAN CLAMP", SIDEBAR_W - 20, 20, COL_TAN));
    float aMin3 = 0.1f, aMax3 = 1.0f;
    sidebar->addSubWidget(std::make_unique<Optikos::Slider>(
        SIDEBAR_W - 20, 18, Optikos::Vec2{0, 0}, Optikos::OPTIKOS_FLOAT, &ampTan, &aMin3, &aMax3));

    sidebar->addSubWidget(mkSep(SIDEBAR_W - 20));
    sidebar->addSubWidget(mkLabel("POINTS", SIDEBAR_W - 20, 20, COL_TEXT_DIM));
    float ppMin = 10.0f, ppMax = (float) MAX_PLOT_PTS;
    sidebar->addSubWidget(std::make_unique<Optikos::Slider>(SIDEBAR_W - 20, 18, Optikos::Vec2{0, 0},
                                                            Optikos::OPTIKOS_FLOAT, &plotPtsF,
                                                            &ppMin, &ppMax));

    sidebar->resize(SIDEBAR_W, WIN_H - TOPBAR_H);

    const char*    gNames[] = {"sin(x + t)", "cos(x + t)", "tan(x + t)"};
    Optikos::Color gCols[]  = {COL_SIN, COL_COS, COL_TAN};

    for (int g = 0; g < GRAPH_COUNT; g++)
    {
        float gy = GRAPHS_Y + g * (GRAPH_H + GRAPH_GAP);

        app.addWidget(100 + g, std::make_unique<Optikos::Container>(
                                   (int) MAIN_W, (int) GRAPH_H, Optikos::Vec2{MAIN_X, gy}, COL_BG));

        for (int li = 0; li <= 4; li++)
        {
            float ly = gy + (GRAPH_H / 4.0f) * li;
            app.addWidget(200 + g * 10 + li,
                          std::make_unique<Optikos::Container>(
                              (int) MAIN_W, 1, Optikos::Vec2{MAIN_X, ly}, COL_GRID));
        }

        float zeroY = gy + GRAPH_H * 0.5f;
        app.addWidget(300 + g, std::make_unique<Optikos::Container>(
                                   (int) MAIN_W, 1, Optikos::Vec2{MAIN_X, zeroY}, COL_ZERO));

        app.addWidget(400 + g,
                      std::make_unique<Optikos::Label>(gNames[g], Optikos::Vec2{MAIN_X + 6, gy + 4},
                                                       140, 20, gCols[g]));

        app.addWidget(500 + g, std::make_unique<Optikos::Label>(
                                   "+1", Optikos::Vec2{MAIN_X - 22, gy + 2}, 20, 16, COL_TEXT_DIM));
        app.addWidget(600 + g, std::make_unique<Optikos::Label>(
                                   "-1", Optikos::Vec2{MAIN_X - 22, gy + GRAPH_H - 18}, 20, 16,
                                   COL_TEXT_DIM));
        app.addWidget(700 + g, std::make_unique<Optikos::Label>(
                                   " 0", Optikos::Vec2{MAIN_X - 22, gy + GRAPH_H * 0.5f - 8}, 20,
                                   16, COL_SEPARATOR));
    }

    constexpr int      PT_SIZE = 2;
    constexpr uint32_t PTBASE  = 10000;

    struct PlotPt
    {
        Optikos::Container* w;
    };
    std::vector<std::vector<PlotPt>> pts(GRAPH_COUNT, std::vector<PlotPt>(MAX_PLOT_PTS));

    for (int g = 0; g < GRAPH_COUNT; g++)
    {
        for (int i = 0; i < MAX_PLOT_PTS; i++)
        {
            uint32_t id = PTBASE + g * MAX_PLOT_PTS + i;
            pts[g][i].w =
                app.addWidget(id, std::make_unique<Optikos::Container>(
                                      PT_SIZE, PT_SIZE, Optikos::Vec2{-100.f, -100.f}, gCols[g]));
        }
    }

    using clock = std::chrono::high_resolution_clock;
    auto  last  = clock::now();
    float t     = 0.f;

    while (!app.should_close())
    {
        auto  now = clock::now();
        float dt  = std::chrono::duration<float>(now - last).count();
        last      = now;

        if (!paused) t += dt * speed;

        {
            char buf[32];
            std::snprintf(buf, sizeof(buf), "t = %.2f", t);
            timeLabel->setText(buf);
        }

        int   plotPts = (int) plotPtsF;
        float ptW     = MAIN_W / (float) plotPts;

        for (int i = 0; i < plotPts; i++)
        {
            float x  = (float) i / plotPts * 4.0f * 3.14159f * freq;
            float px = MAIN_X + i * ptW;

            {
                float v  = std::sin(x + t) * ampSin;
                float gy = GRAPHS_Y + 0 * (GRAPH_H + GRAPH_GAP);
                float py = gy + GRAPH_H * 0.5f - v * (GRAPH_H * 0.45f);
                if (pts[0][i].w) pts[0][i].w->setPosition(Optikos::Vec2{px, py});
            }
            {
                float v  = std::cos(x + t) * ampCos;
                float gy = GRAPHS_Y + 1 * (GRAPH_H + GRAPH_GAP);
                float py = gy + GRAPH_H * 0.5f - v * (GRAPH_H * 0.45f);
                if (pts[1][i].w) pts[1][i].w->setPosition(Optikos::Vec2{px, py});
            }
            {
                float raw = std::tan(x + t);
                float v   = raw > ampTan * 10.f    ? ampTan * 10.f
                            : raw < -ampTan * 10.f ? -ampTan * 10.f
                                                   : raw;
                v /= 10.f;
                float gy = GRAPHS_Y + 2 * (GRAPH_H + GRAPH_GAP);
                float py = gy + GRAPH_H * 0.5f - v * (GRAPH_H * 0.45f);
                if (pts[2][i].w) pts[2][i].w->setPosition(Optikos::Vec2{px, py});
            }
        }

        for (int g = 0; g < GRAPH_COUNT; g++)
            for (int i = plotPts; i < MAX_PLOT_PTS; i++)
                if (pts[g][i].w) pts[g][i].w->setPosition(Optikos::Vec2{-100.f, -100.f});

        app.begin();
        app.end();
    }
}