#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include "ui/Widget.hpp"

class Button : public Widget
{
   public:
    Button(uint32_t width, uint32_t height, vec2 position, const std::string& text = "",
           Color color = {0, 0, 0, 1}, std::function<void()> event = nullptr);

    void render(Optikos::IRenderQueue& renderQueue) override;
    void updateVertices() override;
    void handleEvent() override;
    void handleHover(double x, double y) override;
    void resetHover() override;
    bool wantsHoverEvents() const override;
    void resize(int width, int height) override;

    void setHoverDimming(float dimming);  // 0.0 - 255.0
    void setEvent(std::function<void()> event);
    void setText(std::string text);
    void setPosition(vec2 pos) override;

    const std::vector<float>&        getVertices() const override;
    const std::vector<unsigned int>& getIndices() const override;

   private:
    RenderData            m_data;
    Color                 m_color;
    Color                 m_originalColor = m_color;
    Color                 m_dimmed  = m_color;
    bool                  m_isHover = false;
    std::string           m_text;
    std::function<void()> m_event;
};

#endif /* BUTTON_H */