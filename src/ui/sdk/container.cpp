#include "ui/sdk/container.hpp"

Container::Container(uint32_t width, uint32_t height, vec2 position, Color color, bool isVisible)
    : Widget(width, height, position, isVisible), m_color(color)
{
    updateVertices();

    m_data.indices = {0, 1, 2, 2, 3, 0};
}

void Container::render(Optikos::IRenderQueue& renderQueue)
{
    IWidget::render(renderQueue);
    updateLayout();
    for (auto& subWidget : m_subWidgets)
    {
        subWidget->render(renderQueue);
    }
}

void Container::updateVertices()
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

bool Container::handleClick(double x, double y)
{
    for (auto it = m_subWidgets.rbegin(); it != m_subWidgets.rend(); ++it)
    {
        if ((*it)->handleClick(x, y))
        {
            return true;
        }
    }

    if (getClickable() && isInside(x, y))
    {
        handleEvent();  // Currently Container don't have any events like drag etc...
        return true;
    }

    return false;
}

void Container::setPosition(vec2 pos)
{
    m_position = pos;

    updateVertices();

    m_needsLayout = true;
}

const std::vector<float>& Container::getVertices() const
{
    return m_data.vertices;
}

const std::vector<unsigned int>& Container::getIndices() const
{
    return m_data.indices;
}

void Container::resize(int width, int height)
{
    m_width  = width;
    m_height = height;

    updateVertices();

    m_needsLayout = true;
}

void Container::handleEvent()
{
    return; /* stub */
}

void Container::addSubWidget(std::unique_ptr<IWidget> widget)
{
    // TODO: return raw ptr with widget.get() to able reuse the widget after adding to subWidgets.
    if (this != widget.get())
    {
        m_subWidgets.push_back(std::move(widget));
        m_needsLayout = true;
    }
    else
        LOG_DEBUG("addSubWidget add [this] to [this]", "log");
}

void Container::updateLayout()
{
    if (!m_needsLayout) return;
    for (int i = 0; i < m_subWidgets.size(); i++)
    {
        alignWidget(m_subWidgets[i].get(), i);
    }
    m_needsLayout = false;
}

void Container::setAlignment(int alignment)
{
    assert(alignment >= 0 && alignment <= 2);
    /* 0 = from left, 1 = middle, 2 = from right */  // TODO: make enums/defines
    if (m_subAlignment != alignment)
    {
        m_subAlignment = alignment;
        m_needsLayout  = true;
    }
}

void Container::setInterval(int interval)
{
    if (m_interval != interval)
    {
        m_interval    = interval;
        m_needsLayout = true;
    }
}

void Container::setOffset(int offset)
{
    assert(offset >= 0);
    if (m_offset != offset)
    {
        m_offset      = offset;
        m_needsLayout = true;
    }
}

void Container::alignWidget(IWidget* subWidget, int index)
{
    // TODO: need optimization
    vec2  newPos;
    float xPos = 0.0f;

    float totalWidth = 0.0f;
    for (const auto& widget : m_subWidgets)
    {
        totalWidth += static_cast<float>(widget->getWidth());
    }
    if (m_subWidgets.size() > 1)
    {
        totalWidth += static_cast<float>((m_subWidgets.size() - 1) * m_interval);
    }

    float prefixWidth = 0.0f;
    for (int i = 0; i < index; ++i)
    {
        prefixWidth += static_cast<float>(m_subWidgets[i]->getWidth());
        if (i > 0)
        {
            prefixWidth += static_cast<float>(m_interval);
        }
    }
    if (index > 0)
    {
        prefixWidth += static_cast<float>(m_interval);
    }

    switch (m_subAlignment)
    {
        case 0:
            xPos = m_position.x + m_offset + prefixWidth;
            break;
        case 1:
        {
            float startX = m_position.x + (m_width / 2.0f) - (totalWidth / 2.0f);
            xPos         = startX + prefixWidth;
        }
        break;
        case 2:
        {
            float startX = m_position.x + m_width - totalWidth - m_offset;
            xPos         = startX + prefixWidth;
        }
        break;
        default:
            xPos = m_position.x + m_offset + prefixWidth;
            break;
    }

    newPos = {xPos, m_position.y};
    subWidget->setPosition(newPos);
}

bool Container::wantsHoverEvents() const
{
    for (const auto& widget : m_subWidgets)
    {
        if (widget->wantsHoverEvents()) return true;
    }
    return false;
}

void Container::handleHover(double x, double y)
{
    for (auto& subWidget : m_subWidgets)
    {
        if (!subWidget->wantsHoverEvents())
        {
            subWidget->resetHover();
            continue;
        }

        if (subWidget->isInside(x, y))
        {
            subWidget->handleHover(x, y);
            return;
        }
        else
            subWidget->resetHover();
    }
}