#ifndef OPTIKOS_H
#define OPTIKOS_H

#include <memory>

#include "input/IInputSystem.hpp"
#include "platform/IWindow.hpp"
#include "render/IRenderer.hpp"
#include "ui/UISystem.hpp"

namespace Optikos
{
class Optikos
{
   public:
    Optikos(std::unique_ptr<IWindow> window, std::unique_ptr<IRenderer> renderer,
            std::unique_ptr<IInputSystem> inputSystem, std::unique_ptr<UISystem> uiSystem,
            GraphicsConfig config);

    void run();

   private:
    std::unique_ptr<IRenderer>    m_renderer;
    std::unique_ptr<IWindow>      m_window;
    std::unique_ptr<IInputSystem> m_inputSystem;
    std::unique_ptr<UISystem>     m_uiSystem;

    GraphicsConfig m_config;
};

}  // namespace Optikos

#endif /* OPTIKOS_H */