#include "ui/sdk/container.hpp"

Container::Container(uint32_t width, uint32_t height, vec2 position, Color color, bool isVisible)
    : m_attributes({isVisible, position, width, height}), m_color(color)
{
    m_data.vertices = {position.x,         position.y,          color.r, color.g, color.b, color.a,
                       position.x + width, position.y,          color.r, color.g, color.b, color.a,
                       position.x + width, position.y + height, color.r, color.g, color.b, color.a,
                       position.x,         position.y + height, color.r, color.g, color.b, color.a};

    m_data.indices = {0, 1, 2, 2, 3, 0};
}

vec2 Container::getPosition() const
{
    return m_attributes.position;
}

uint32_t Container::getWidth() const
{
    return m_attributes.width;
}

uint32_t Container::getHeight() const
{
    return m_attributes.height;
}

const std::vector<float>& Container::getVertices() const
{
    return m_data.vertices;
}

const std::vector<unsigned int>& Container::getIndices() const
{
    return m_data.indices;
}

bool Container::getVisible() const
{
    return m_attributes.isVisible;
}

void Container::handleEvent()
{
    return; /* stub */
}