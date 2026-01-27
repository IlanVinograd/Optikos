#ifndef CONTAINER_H
#define CONTAINER_H

#include "ui/Widget.hpp"

class Container : public Widget
{
   public:
    Container(uint32_t width, uint32_t height, vec2 position, Color color = {0, 0, 0, 1},
              bool isVisible = true);  // simple rectangle container

    void                             render(Optikos::IRenderQueue& renderQueue) override;
    void                             updateVertices() override;
    const std::vector<float>&        getVertices() const override;
    const std::vector<unsigned int>& getIndices() const override;
    void                             handleEvent() override;
    bool                             handleClick(double x, double y) override;
    void                             handleHover(double x, double y) override;
    bool                             wantsHoverEvents() const override;
    void                             resize(int width, int height) override;
    void                             setPosition(vec2 pos) override;

    void addSubWidget(std::unique_ptr<IWidget> widget);
    void setAlignment(int alignment);
    void setInterval(int interval);
    void setOffset(int offset);

   private:
    void alignWidget(IWidget* subWidget, int i);
    void updateLayout();

    RenderData                            m_data;
    Color                                 m_color;
    int                                   m_subAlignment = 0;
    int                                   m_offset       = 0;
    int                                   m_interval     = 0;
    bool                                  m_needsLayout  = true;
    std::vector<std::unique_ptr<IWidget>> m_subWidgets;
};

#endif /* CONTAINER_H */