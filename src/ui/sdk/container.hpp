#ifndef CONTAINER_H
#define CONTAINER_H

#include "ui/IWidget.hpp"

class Container : public IWidget
{
   public:
    Container(uint32_t width, uint32_t height, vec2 position, Color color = {0, 0, 0, 1},
              bool isVisible = true);  // simple rectangle container

    void                             render(Optikos::IRenderQueue& renderQueue) override;
    vec2                             getPosition() const override;
    void                             setPosition(vec2 pos) override;
    uint32_t                         getWidth() const override;
    uint32_t                         getHeight() const override;
    const std::vector<float>&        getVertices() const override;
    const std::vector<unsigned int>& getIndices() const override;
    void                             handleEvent() override;
    bool                             getVisible() const override;
    bool                             getClickable() const override;
    bool                             handleClick(double x, double y) override;
    void                             setClickable(bool isClickable) override;
    void                             resize(int width, int height) override;
    void                             setAutoExpand(int isExpand) override;
    int                              isExpand() override;

    void addSubWidget(std::unique_ptr<IWidget> widget);
    void setAlignment(int alignment);
    void setInterval(int interval);
    void setOffset(int offset);

   private:
    void alignWidget(IWidget* subWidget, int i);
    void updateLayout();

    Attributes m_attributes;
    RenderData m_data;
    Color      m_color;

    int                                   m_subAlignment = 0;
    int                                   m_offset       = 0;
    int                                   m_interval     = 0;
    bool                                  m_needsLayout  = true;
    std::vector<std::unique_ptr<IWidget>> m_subWidgets;
};

#endif /* CONTAINER_H */