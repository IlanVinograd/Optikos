#ifndef CONTAINER_H
#define CONTAINER_H

#include "ui/IWidget.hpp"

class Container : public IWidget
{
   public:
    Container(uint32_t width, uint32_t heigth, vec2 position,
              Color color = {0, 0, 0, 1});  // simple rectangle conatiner

    vec2                      getPosition() override;
    uint32_t                  getWidth() const override;
    uint32_t                  getHeight() const override;
    std::vector<float>        getVertices() const override;
    std::vector<unsigned int> getIndices() const override;

   private:
    vec2       m_position;  // left top corner
    uint32_t   m_width;
    uint32_t   m_height;
    RenderData m_data;
    Color      m_color;
};

#endif /* CONTAINER_H */