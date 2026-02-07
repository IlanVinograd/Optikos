#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include "ui/Widget.hpp"
#include "ui/text/TextFont.hpp"

namespace Optikos
{
class Button : public Widget
{
   public:
    explicit Button(uint32_t width, uint32_t height, Vec2 position);
    explicit Button(uint32_t width, uint32_t height, Vec2 position, const std::string& text);
    explicit Button(uint32_t width, uint32_t height, Vec2 position, std::function<void()> event);

    void render(IRenderQueue& renderQueue) override;
    void updateData() override;
    void handleEvent() override;
    void handleHover(double x, double y) override;
    void resetHover() override;
    bool wantsHoverEvents() const override;
    void resize(int width, int height) override;

    void setHoverDimming(float dimming);  // 0.0 - 255.0
    void setEvent(std::function<void()> event);
    void setText(std::string text);
    void setFont(std::string font);
    void setPosition(Vec2 pos) override;

    const std::vector<float>&        getVertices() const override;
    const std::vector<unsigned int>& getIndices() const override;

   private:
    RenderData            m_data;
    RenderData            m_textData;
    Color                 m_originalColor = m_color;
    Color                 m_dimmed        = m_color;
    bool                  m_isHover       = false;
    std::string           m_text          = "";
    float                 m_fontSize      = DEFAULT0_FONTSIZE;
    std::string           m_fontName      = DEFAULT0_FONT;
    std::function<void()> m_event         = nullptr;
};

}  // namespace Optikos

#endif /* BUTTON_H */