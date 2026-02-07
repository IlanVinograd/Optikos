#ifndef OPTIKOS_H
#define OPTIKOS_H
#include "optikos_config.hpp"

#include <memory>

#include "input/IInputSystem.hpp"
#include "platform/IWindow.hpp"
#include "render/IRenderer.hpp"
#include "ui/UISystem.hpp"
#include "ui/text/TextFont.hpp"

#include "utilities/vec.hpp"

// TODO: wrap to .hpp
#include "ui/sdk/button.hpp"
#include "ui/sdk/container.hpp"

unsigned int constexpr DEFAULT_WIDTH  = 800;
unsigned int constexpr DEFAULT_HEIGHT = 600;

namespace Optikos
{
class Optikos
{
   public:
    Optikos(std::string_view title, unsigned int width = DEFAULT_WIDTH,
                     unsigned int height = DEFAULT_HEIGHT);

    bool should_close();
    void begin();
    void end();

    void pushFont(std::string_view path, std::string fontName = DEFAULT0_FONT,
                  float fontSize = DEFAULT0_FONTSIZE);
    void setWindowTitleBar(Color color);

    template <typename T>
    T* addWidget(const uint32_t idx, std::unique_ptr<T> widget)
    {
        return m_uiSystem->add_widget(idx, std::move(widget));
    }

    bool removeWidget(uint32_t id);

   private:
    std::unique_ptr<IRenderer>    m_renderer;
    std::unique_ptr<IWindow>      m_window;
    std::unique_ptr<IInputSystem> m_inputSystem;
    std::unique_ptr<UISystem>     m_uiSystem;
};

}  // namespace Optikos

#endif /* OPTIKOS_H */