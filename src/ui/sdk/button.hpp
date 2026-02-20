#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include "ui/Widget.hpp"
#include "ui/sdk/label.hpp"
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
    void setPosition(Vec2 pos) override;
    void setColor(Color color) override;

    void setHoverDimming(float dimming);  // 0.0 - 255.0
    void setEvent(std::function<void()> event);
    void setHoverEvent(std::function<void()> event);
    void setText(std::string text);
    void setFont(std::string font);
    void setTextColor(Color color);

    const std::vector<Vertex>&        getVertices() const override;
    const std::vector<unsigned int>& getIndices() const override;

    bool isHover() const;
    
   private:
    RenderData m_data;
    Color      m_originalColor;
    Color      m_dimmed;
    bool       m_isHover   = false;
    Color      m_textColor = DEFAULT_COLOR;

    std::unique_ptr<Label> m_label;
    std::function<void()>  m_event = nullptr;
    std::function<void()>  m_hoverEvent = nullptr;
};

}  // namespace Optikos

#endif /* BUTTON_H */