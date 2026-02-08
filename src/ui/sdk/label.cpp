#include "ui/sdk/label.hpp"
// TODO: set text
namespace Optikos
{
Label::Label(std::string text, Vec2 position, Color color)
    : Widget(DEFAULT_LABEL_WIDTH, DEFAULT_LABEL_HEIGHT, position, true, color)
{
    m_text = text;

    Vec2 size = TextFont::getInstance().getSizeText(m_text, m_fontName);
    m_width   = static_cast<uint32_t>(size.x);
    m_height  = static_cast<uint32_t>(size.y);

    updateData();
}

void Label::render(IRenderQueue& renderQueue)
{
    DrawCommand cmd;
    cmd.vertices  = getVertices();
    cmd.indices   = getIndices();
    cmd.shaderId  = 0;
    cmd.textureId = TextFont::getInstance().getAtlasTextureId(m_fontName);
    renderQueue.submit(std::move(cmd));
}

void Label::updateData()
{
    m_data = TextFont::getInstance().generateTextQuads(m_text, m_position, m_width, m_height,
                                                       m_fontName, m_color);
}

const std::vector<float>& Label::getVertices() const
{
    return m_data.vertices;
}

const std::vector<unsigned int>& Label::getIndices() const
{
    return m_data.indices;
}

void Label::setPosition(Vec2 pos)
{
    m_position = pos;
    updateData();
}

void Label::handleEvent()
{
    return; /* stub */
}
bool Label::handleClick(double x, double y)
{
    (void) x;
    (void) y;
    return false; /* stub */
}
void Label::handleHover(double x, double y)
{
    (void) x;
    (void) y;
    return; /* stub */
}
void Label::resetHover()
{
    return; /* stub */
}
bool Label::wantsHoverEvents() const
{
    return false; /* stub */
}
void Label::resize(int width, int height)
{
    m_width  = width;
    m_height = height;
    updateData();
}

}  // namespace Optikos
