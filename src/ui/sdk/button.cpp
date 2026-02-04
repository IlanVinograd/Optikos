#include "ui/sdk/button.hpp"

#include "ui/text/TextFont.hpp"

Button::Button(uint32_t width, uint32_t height, vec2 position) : Widget(width, height, position)
{
    setHoverDimming(0.5);

    updateData();

    m_isClickable = true;
}

Button::Button(uint32_t width, uint32_t height, vec2 position, const std::string& text)
    : Button(width, height, position)
{
    m_text = text;
    updateData();
}

Button::Button(uint32_t width, uint32_t height, vec2 position, std::function<void()> event)
    : Button(width, height, position)
{
    m_event = event;
}

void Button::render(Optikos::IRenderQueue& renderQueue)
{
    if (!m_isVisible) return;

    Optikos::DrawCommand bgCmd;
    bgCmd.vertices  = m_data.vertices;
    bgCmd.indices   = m_data.indices;
    bgCmd.shaderId  = 0;
    bgCmd.textureId = 0;
    renderQueue.submit(std::move(bgCmd));

    if (!m_text.empty())
    {
        Optikos::DrawCommand textCmd;
        textCmd.vertices  = m_textData.vertices;
        textCmd.indices   = m_textData.indices;
        textCmd.shaderId  = 0;
        textCmd.textureId = TextFont::getInstance().getAtlasTextureId(m_fontName);
        renderQueue.submit(std::move(textCmd));
    }
}

void Button::updateData()
{
    m_data.indices  = {0, 1, 2, 2, 3, 0};
    m_data.vertices = {m_position.x,
                       m_position.y,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,
                       0.0,
                       0.0,
                       m_position.x + m_width,
                       m_position.y,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,
                       0.0,
                       0.0,
                       m_position.x + m_width,
                       m_position.y + m_height,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,
                       0.0,
                       0.0,
                       m_position.x,
                       m_position.y + m_height,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,
                       0.0,
                       0.0};

    if (!m_text.empty())
    {
        m_textData = TextFont::getInstance().generateTextQuads(m_text, m_position, m_width, m_height, m_fontName);
    }
}

void Button::handleEvent()
{
    if (m_event != nullptr) m_event();
}

void Button::handleHover(double x, double y)
{
    (void) x;
    (void) y;
    if (!m_isHover)
    {
        m_isHover = true;
        m_color   = m_dimmed;
        updateData();
    }
}

void Button::resetHover()
{
    m_isHover = false;
    m_color   = m_originalColor;
    updateData();
}

bool Button::wantsHoverEvents() const
{
    return true;
}

void Button::resize(int width, int height)
{
    m_width  = width;
    m_height = height;

    updateData();
}

void Button::setHoverDimming(float dimming)
{
    assert(0.0f <= dimming && dimming <= 1.0f);
    m_dimmed.r = m_originalColor.r * dimming;
    m_dimmed.g = m_originalColor.g * dimming;
    m_dimmed.b = m_originalColor.b * dimming;
    m_dimmed.a = m_originalColor.a;
}

void Button::setEvent(std::function<void()> event)
{
    assert(event != nullptr);
    m_event = event;
}

const std::vector<float>& Button::getVertices() const
{
    return m_data.vertices;
}
const std::vector<unsigned int>& Button::getIndices() const
{
    return m_data.indices;
}

void Button::setText(std::string text)
{
    m_text = text;
}

void Button::setFont(std::string font)
{
    m_fontName = font;
    
    updateData();
}

void Button::setPosition(vec2 pos)
{
    m_position = pos;

    updateData();
}