#include "ui/sdk/button.hpp"

Button::Button(uint32_t width, uint32_t height, vec2 position, const std::string& text, Color color,
               std::function<void()> event)
    : Widget(width, height, position),
      m_originalColor(color),
      m_color(color),
      m_dimmed(color),
      m_text(text),
      m_event(event)
{
    setHoverDimming(0.5);
    updateVertices();

    m_data.indices = {0, 1, 2, 2, 3, 0};

    m_isClickable = true;
}

void Button::render(Optikos::IRenderQueue& renderQueue)
{
    if (m_isClickable)
    {
        IWidget::render(renderQueue);
    }
}

void Button::updateVertices()
{
    m_data.vertices = {m_position.x,
                       m_position.y,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,
                       m_position.x + m_width,
                       m_position.y,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,
                       m_position.x + m_width,
                       m_position.y + m_height,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,
                       m_position.x,
                       m_position.y + m_height,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a};
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
        updateVertices();
    }
}

void Button::resetHover()
{
    m_isHover = false;
    m_color   = m_originalColor;
    updateVertices();
}

bool Button::wantsHoverEvents() const
{
    return true;
}

void Button::resize(int width, int height)
{
    m_width  = width;
    m_height = height;

    updateVertices();
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

void Button::setPosition(vec2 pos)
{
    m_position = pos;

    updateVertices();
}