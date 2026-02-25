#include "ui/sdk/slider.hpp"

namespace Optikos
{
Slider::Slider(uint32_t width, uint32_t height, Vec2 position, OptikosType type, void* value,
               const void* min, const void* max)
    : Widget(width, height, position),
      m_value(value),
      m_max(max),
      m_min(min),
      m_type(type),
      m_dimmed(m_color),
      m_originalColor(m_color)
{
    if (m_min > m_max)
        LOG_WARN("Slider was created with values m_min > m_max.", "log"); 

    setHoverDimming(0.5);

    updateData();

    m_isClickable = true;
}

void Slider::render(IRenderQueue& renderQueue)
{
    if (!m_isVisible) return;

    DrawCommand cmd;
    cmd.vertices  = getVertices();
    cmd.indices   = getIndices();
    cmd.shaderId  = 0;
    cmd.textureId = 0;
    renderQueue.submit(std::move(cmd));
}

void Slider::updateData()
{
    float sliderPos = findSlider(m_type, m_value);
    m_sliderHeight  = (float) m_height + 6;
    m_sliderWidth   = 16.0f;

    float sliderOverhang = (m_height - m_sliderHeight) / 2;

    m_data.indices = {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 8, 9, 10, 10, 11, 8};

    m_data.vertices = {
        {m_position.x, m_position.y, m_leftColor.r, m_leftColor.g, m_leftColor.b, m_leftColor.a, 0,
         0, m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},

        {m_position.x + sliderPos, m_position.y, m_leftColor.r, m_leftColor.g, m_leftColor.b,
         m_leftColor.a, 0, 0, m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},

        {m_position.x + sliderPos, m_position.y + m_height, m_leftColor.r, m_leftColor.g,
         m_leftColor.b, m_leftColor.a, 0, 0, m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},

        {m_position.x, m_position.y + m_height, m_leftColor.r, m_leftColor.g, m_leftColor.b,
         m_leftColor.a, 0, 0, m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},

        {m_position.x + sliderPos, m_position.y, m_rightColor.r, m_rightColor.g, m_rightColor.b,
         m_rightColor.a, 0, 0, m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},

        {m_position.x + m_width, m_position.y, m_rightColor.r, m_rightColor.g, m_rightColor.b,
         m_rightColor.a, 0, 0, m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},

        {m_position.x + m_width, m_position.y + m_height, m_rightColor.r, m_rightColor.g,
         m_rightColor.b, m_rightColor.a, 0, 0, m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},

        {m_position.x + sliderPos, m_position.y + m_height, m_rightColor.r, m_rightColor.g,
         m_rightColor.b, m_rightColor.a, 0, 0, m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},

        {m_position.x + sliderPos - m_sliderWidth / 2, m_position.y + sliderOverhang,
         m_sliderColor.r, m_sliderColor.g, m_sliderColor.b, m_sliderColor.a, 0, 0,
         m_clip.xMin - m_sliderWidth / 2, m_clip.xMax + m_sliderWidth / 2,
         m_clip.yMin + sliderOverhang, m_clip.yMax - sliderOverhang},

        {m_position.x + sliderPos + m_sliderWidth / 2, m_position.y + sliderOverhang,
         m_sliderColor.r, m_sliderColor.g, m_sliderColor.b, m_sliderColor.a, 0, 0,
         m_clip.xMin - m_sliderWidth / 2, m_clip.xMax + m_sliderWidth / 2,
         m_clip.yMin + sliderOverhang, m_clip.yMax - sliderOverhang},

        {m_position.x + sliderPos + m_sliderWidth / 2, m_position.y + m_height - sliderOverhang,
         m_sliderColor.r, m_sliderColor.g, m_sliderColor.b, m_sliderColor.a, 0, 0,
         m_clip.xMin - m_sliderWidth / 2, m_clip.xMax + m_sliderWidth / 2,
         m_clip.yMin + sliderOverhang, m_clip.yMax - sliderOverhang},

        {m_position.x + sliderPos - m_sliderWidth / 2, m_position.y + m_height - sliderOverhang,
         m_sliderColor.r, m_sliderColor.g, m_sliderColor.b, m_sliderColor.a, 0, 0,
         m_clip.xMin - m_sliderWidth / 2, m_clip.xMax + m_sliderWidth / 2,
         m_clip.yMin + sliderOverhang, m_clip.yMax - sliderOverhang}};
}

void Slider::handleDrag(double x, double y)
{
    (void) y;

    if (!m_onHold) return;

    float newPos = (float) x - m_position.x;
    newPos       = std::clamp(newPos, 0.0f, (float) m_width);

    switch (m_type)
    {
        case OPTIKOS_INT:
        {
            float min       = (float) (*(int*) m_min);
            float max       = (float) (*(int*) m_max);
            float ratio     = newPos / m_width;
            int   newValue  = (int) (min + ratio * (max - min));
            *(int*) m_value = newValue;
            break;
        }
        case OPTIKOS_FLOAT:
        {
            float min         = *(float*) m_min;
            float max         = *(float*) m_max;
            float ratio       = newPos / m_width;
            float newValue    = min + ratio * (max - min);
            *(float*) m_value = newValue;
            break;
        }
    }

    updateData();
}

float Slider::findSlider(OptikosType type, void* data) const
{
    switch (type)
    {
        case OPTIKOS_INT:
        {
            float min   = (float) (*(int*) m_min);
            float max   = (float) (*(int*) m_max);
            float value = std::clamp((float) (*(int*) data), min, max);

            return (value - min) / (max - min) * m_width;
        }

        case OPTIKOS_FLOAT:
        {
            float min   = *(float*) m_min;
            float max   = *(float*) m_max;
            float value = std::clamp(*(float*) data, min, max);

            return (value - min) / (max - min) * m_width;
        }

        default:
        {
            LOG_ERROR("Not valid type inside [findSlider]", "log");
            return 0.0f;
        }
    }
}

const std::vector<Vertex>& Slider::getVertices() const
{
    return m_data.vertices;
}

const std::vector<unsigned int>& Slider::getIndices() const
{
    return m_data.indices;
}

void Slider::handleEvent()
{
    /* stub */
}

bool Slider::handleClick(double x, double y, int action)
{
    if (getClickable() && isInside(x, y) && action == LEFT_CLICK)
    {
        m_onHold = true;
        return true;
    }
    else if (action == RELEASE && m_onHold)
    {
        m_onHold = false;
        resetHover();
        return true;
    }

    return false;
}

void Slider::handleHover(double x, double y)
{
    bool insideGrab = isInsideGrab(x, y);

    if (insideGrab && !m_isHover)
    {
        m_isHover     = true;
        m_sliderColor = m_dimmed;
        updateData();
    }
    else if (!insideGrab && m_isHover)
    {
        m_isHover     = false;
        m_sliderColor = m_originalColor;
        updateData();
    }
}

bool Slider::isInsideGrab(double x, double y) const
{
    float sliderPos      = findSlider(m_type, m_value);
    float sliderOverhang = (m_height - m_sliderHeight) / 2;

    Clip clip = getClip();

    bool inSlider =
        (m_position.x + sliderPos - m_sliderWidth / 2 <= x &&
         x <= m_position.x + sliderPos + m_sliderWidth / 2 && m_position.y + sliderOverhang <= y &&
         y <= m_position.y + m_height - sliderOverhang);

    bool inClip = (clip.xMin - m_sliderWidth / 2 <= x && x <= clip.xMax + m_sliderWidth / 2 &&
                   clip.yMin + sliderOverhang <= y && y <= clip.yMax - sliderOverhang);

    return inSlider && inClip;
}

void Slider::resetHover()
{
    if (m_onHold) return;

    m_isHover     = false;
    m_sliderColor = m_originalColor;
    updateData();
}
bool Slider::wantsHoverEvents() const
{
    return true;
}

void Slider::resize(int width, int height)
{
    m_width  = width;
    m_height = height;

    updateData();
}

void Slider::setPosition(Vec2 pos)
{
    m_position = pos;
    updateData();
}

void Slider::setColor(Color color)
{
    m_color         = color;
    m_originalColor = color;

    setHoverDimming(0.5);

    updateData();
}

void Slider::setHoverDimming(float dimming)
{
    assert(0.0f <= dimming && dimming <= 1.0f);
    m_dimmed.r = static_cast<unsigned char>(std::min(m_originalColor.r * dimming, 255.0f));
    m_dimmed.g = static_cast<unsigned char>(std::min(m_originalColor.g * dimming, 255.0f));
    m_dimmed.b = static_cast<unsigned char>(std::min(m_originalColor.b * dimming, 255.0f));
    m_dimmed.a = m_originalColor.a;
}

}  // namespace Optikos