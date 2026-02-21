#ifndef SLIDER_H
#define SLIDER_H

#include "ui/Widget.hpp"

namespace Optikos
{
constexpr Color DEFAULT_COLOR1 = {0, 128, 255, 255};
constexpr Color DEFAULT_COLOR2 = {0, 0, 153, 255};

enum OptikosType
{
    OPTIKOS_INT,
    OPTIKOS_FLOAT
};

class Slider : public Widget
{
   public:
    Slider(uint32_t width, uint32_t height, Vec2 position, OptikosType type, void* value,
           const void* min, const void* max);

    void                             render(IRenderQueue& renderQueue) override;
    void                             updateData() override;
    const std::vector<Vertex>&       getVertices() const override;
    const std::vector<unsigned int>& getIndices() const override;
    void                             handleEvent() override;
    bool                             handleClick(double x, double y, int action) override;
    void                             handleHover(double x, double y) override;
    void                             resetHover() override;
    bool                             wantsHoverEvents() const override;
    void                             resize(int width, int height) override;
    void                             setPosition(Vec2 pos) override;
    void                             setColor(Color color) override;
    void                             handleDrag(double x, double y) override;

   private:
    float findSlider(OptikosType type, void* data) const;
    void  setHoverDimming(float dimming);
    bool  isInsideGrab(double x, double y) const;

    float m_sliderWidth;
    float m_sliderHeight;

    void*       m_value;
    const void* m_min;
    const void* m_max;
    OptikosType m_type;

    RenderData m_data;

    Color m_leftColor     = DEFAULT_COLOR1;
    Color m_rightColor    = DEFAULT_COLOR2;
    Color m_sliderColor   = m_color;
    Color m_originalColor = m_color;
    Color m_dimmed;

    bool m_isHover = false;
    bool m_onHold  = false;
};
}  // namespace Optikos

#endif /* SLIDER_H */