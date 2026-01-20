#include "ui/sdk/container.hpp"

Container::Container(uint32_t width, uint32_t height, vec2 position, Color color)
    : m_width(width), m_height(height), m_position(position), m_color(color)
{
    m_data.vertices = {position.x, position.y,         position.x + width,
                       position.y, position.x + width, position.y + height,
                       position.x, position.y + height};

    m_data.indices = {0, 1, 2, 2, 3, 0};
}

vec2 Container::getPosition()
{
    return m_position;
}

uint32_t Container::getWidth() const
{
    return m_width;
}

uint32_t Container::getHeight() const
{
    return m_height;
}

std::vector<float> Container::getVertices() const
{
    return m_data.vertices;
}

std::vector<unsigned int> Container::getIndices() const
{
    return m_data.indices;
}