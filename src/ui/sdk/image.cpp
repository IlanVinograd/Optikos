#include "ui/sdk/image.hpp"

namespace Optikos
{
Image::Image(OpTextureID id, uint32_t width, uint32_t height, Vec2 position)
    : Widget(width, height, position), m_id(id)
{
    m_needUpdate = true;
    updateData();
}

void Image::render(IRenderQueue& renderQueue)
{
    DrawCommand cmd;
    cmd.vertices    = getVertices();
    cmd.indices     = getIndices();
    cmd.shaderId    = 0;
    cmd.textureId   = (unsigned int) m_id;
    cmd.textureMode = TEXTURE_IMG;
    renderQueue.submit(std::move(cmd));
}

void Image::updateData()
{
    if (!m_needUpdate) return;

    m_data.indices = {0, 1, 2, 2, 3, 1};

    m_data.vertices = {
        {m_position.x, m_position.y, m_color.r, m_color.g, m_color.b, m_color.a, 0.0f, 0.0f,
         m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},

        {m_position.x + m_width, m_position.y, m_color.r, m_color.g, m_color.b, m_color.a, 1.0f,
         0.0f, m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},

        {m_position.x, m_position.y + m_height, m_color.r, m_color.g, m_color.b, m_color.a, 0.0f,
         1.0f, m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},

        {m_position.x + m_width, m_position.y + m_height, m_color.r, m_color.g, m_color.b,
         m_color.a, 1.0f, 1.0f, m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax}};

    m_needUpdate = false;
}

const std::vector<Vertex>& Image::getVertices() const
{
    return m_data.vertices;
}
const std::vector<unsigned int>& Image::getIndices() const
{
    return m_data.indices;
}

void Image::resize(int width, int height)
{
    if (m_width != static_cast<uint32_t>(width) || m_height != static_cast<uint32_t>(height))
        m_needUpdate = true;

    m_width  = width;
    m_height = height;

    if (!m_clipSetByParent)
        m_clip = {m_position.x, m_position.x + (float) m_width, m_position.y,
                  m_position.y + (float) m_height};

    updateData();
}

void Image::setPosition(Vec2 pos)
{
    if (m_position != pos) m_needUpdate = true;

    m_position = pos;

    if (!m_clipSetByParent)
        m_clip = {m_position.x, m_position.x + (float) m_width, m_position.y,
                  m_position.y + (float) m_height};

    updateData();
}

void Image::setTexture(OpTextureID id)
{
    m_id = id;
}

void Image::handleEvent()
{
    return; /* stub */
}

}  // namespace Optikos