#ifndef OPTIKOS_H
#define OPTIKOS_H

#include <memory>

#include "input/IInputSystem.hpp"
#include "platform/IWindow.hpp"
#include "render/IRenderer.hpp"
#include "ui/UISystem.hpp"
#include "ui/text/TextFont.hpp"

//TODO: change to more serious lib
#include "utilities/vec.hpp"

//TODO: wrap to .hpp
#include "ui/sdk/button.hpp"
#include "ui/sdk/container.hpp"


namespace Optikos
{
class Optikos
{
   public:
    Optikos(std::unique_ptr<IWindow> window, std::unique_ptr<IRenderer> renderer,
            std::unique_ptr<IInputSystem> inputSystem, std::unique_ptr<UISystem> uiSystem,
            GraphicsConfig config);

    bool should_close();
    void begin();
    void end();

    void pushFont(std::string_view path, std::string fontName = DEFAULT0_FONT,
                  float fontSize = DEFAULT0_FONTSIZE);

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

    GraphicsConfig m_config;
};

}  // namespace Optikos

#endif /* OPTIKOS_H */