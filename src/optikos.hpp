#ifndef OPTIKOS_H
#define OPTIKOS_H

#include "render/IRenderer.hpp"
#include "platform/IWindow.hpp"
#include "input/IInputSystem.hpp"

#include <memory>

namespace Optikos {

class Optikos {
public:
    Optikos(std::unique_ptr<IWindow> window,
            std::unique_ptr<IRenderer> renderer,
            std::unique_ptr<IInputSystem> inputSystem,
            GraphicsConfig config);

    void run();

private:
    std::unique_ptr<IWindow> m_window;
    std::unique_ptr<IRenderer> m_renderer;
    std::unique_ptr<IInputSystem> m_inputSystem;

    GraphicsConfig m_config;
};

} /* Optikos */

#endif /* OPTIKOS_H */