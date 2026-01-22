#include "optikos.hpp"

namespace Optikos
{
Optikos::Optikos(std::unique_ptr<IWindow> window, std::unique_ptr<IRenderer> renderer,
                 std::unique_ptr<IInputSystem> inputSystem, std::unique_ptr<UISystem> uiSystem,
                 GraphicsConfig config)
    : m_renderer(std::move(renderer)),
      m_window(std::move(window)),
      m_inputSystem(std::move(inputSystem)),
      m_uiSystem(std::move(uiSystem)),
      m_config(config)
{
    m_window->setRenderer(m_renderer.get());
    m_window->setWindowTitleBar({25, 25, 25});
}

void Optikos::run()
{
    while (!m_window->should_close())
    {
        m_renderer->beginFrame();

        m_uiSystem->render(m_renderer->getRenderQueue());

        m_renderer->endFrame();
        m_renderer->swap_buffer();
        m_window->poll_events();
    }
}

}  // namespace Optikos