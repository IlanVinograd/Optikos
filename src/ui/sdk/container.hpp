#ifndef CONTAINER_H
#define CONTAINER_H

#include "ui/IWidget.hpp"

class Container : public IWidget
{
   public:
    Container(uint32_t width, uint32_t height, vec2 position, Color color = {0, 0, 0, 1},
              bool isVisible = true);  // simple rectangle container

    vec2                             getPosition() const override;
    uint32_t                         getWidth() const override;
    uint32_t                         getHeight() const override;
    const std::vector<float>&        getVertices() const override;
    const std::vector<unsigned int>& getIndices() const override;
    void                             handleEvent() override;
    bool                             getVisible() const override;
    void                             resize(int width, int height) override;
    void                             setAutoExpand(bool isExpand) override;
    bool                             isExpand() override;

   private:
    Attributes m_attributes;
    RenderData m_data;
    Color      m_color;
};

#endif /* CONTAINER_H */