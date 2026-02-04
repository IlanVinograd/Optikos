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
    m_window->setInputSystem(m_inputSystem.get());
    m_window->setUiSystem(m_uiSystem.get());

    m_window->setWindowTitleBar({25, 25, 25});
}

bool Optikos::should_close()
{
    return m_window->should_close();
}

void Optikos::begin()
{
    m_renderer->beginFrame();
    m_uiSystem->render(m_renderer->getRenderQueue());
}

void Optikos::end()
{
    m_renderer->endFrame();
    m_renderer->swap_buffer();
    m_window->poll_events();
}

void Optikos::pushFont(std::string_view path, std::string fontName, float fontSize)
{
    auto& font = TextFont::getInstance();
    font.loadFont(path, fontName, fontSize);
    unsigned int id = m_renderer->loadTexture(
        font.getAtlasData(fontName), font.getAtlasSize(fontName), font.getAtlasSize(fontName));
    font.setAtlasTextureId(id, fontName);
}

bool Optikos::removeWidget(uint32_t id)
{
    return m_uiSystem->rem_widget(id);
}

}  // namespace Optikos