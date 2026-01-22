#include "ui/sdk/container.hpp"

Container::Container(uint32_t width, uint32_t height, vec2 position, Color color)
    : m_size({width, height}), m_position(position), m_color(color)
{
    m_data.vertices = {position.x, position.y,         position.x + width,
                       position.y, position.x + width, position.y + height,
                       position.x, position.y + height};

    m_data.indices = {0, 1, 2, 2, 3, 0};
}

vec2 Container::getPosition() const
{
    return m_position;
}

uint32_t Container::getWidth() const
{
    return m_size.width;
}

uint32_t Container::getHeight() const
{
    return m_size.height;
}

const std::vector<float>& Container::getVertices() const
{
    return m_data.vertices;
}

const std::vector<unsigned int>& Container::getIndices() const
{
    return m_data.indices;
}