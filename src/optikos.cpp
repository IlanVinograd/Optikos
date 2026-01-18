#include "optikos.hpp"

namespace Optikos
{
Optikos::Optikos(std::unique_ptr<IWindow> window, std::unique_ptr<IRenderer> renderer,
                 std::unique_ptr<IInputSystem> inputSystem, GraphicsConfig config)
    : m_window(std::move(window)),
      m_renderer(std::move(renderer)),
      m_inputSystem(std::move(inputSystem)),
      m_config(config)
{
    m_window->setWindowTitleBar({25, 25, 25});
}

void Optikos::run()
{
    while (!m_window->should_close())
    {
        m_renderer->swap_buffer();
        m_window->poll_events();
    }
}

}  // namespace Optikos