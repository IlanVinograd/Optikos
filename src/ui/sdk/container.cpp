#include "ui/sdk/container.hpp"

namespace Optikos
{
Container::Container(uint32_t width, uint32_t height, Vec2 position, Color color, bool isVisible)
    : Widget(width, height, position, isVisible, color)
{
    updateData();

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

void Container::updateData()
{
    m_data.vertices = {{m_position.x,
                       m_position.y,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,
                       0,
                       0},
                       {m_position.x + m_width,
                       m_position.y,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,
                       0,
                       0},
                       {m_position.x + m_width,
                       m_position.y + m_height,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,
                       0,
                       0},
                       {m_position.x,
                       m_position.y + m_height,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,
                       0,
                       0}};
}

bool Container::handleClick(double x, double y)
{
    for (auto it = m_subWidgets.rbegin(); it != m_subWidgets.rend(); ++it)
    {
        (*it)->handleClick(x, y);
    }

    if (getClickable() && isInside(x, y))
    {
        handleEvent();  // Currently Container don't have any events like drag etc...
        return true;
    }

    return false;
}

void Container::setPosition(Vec2 pos)
{
    m_position = pos;

    updateData();

    m_needsLayout = true;
}

const std::vector<Vertex>& Container::getVertices() const
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

    updateData();

    m_needsLayout = true;
}

void Container::handleEvent()
{
    return; /* stub */
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

void Container::setAlignment(AlignMode mode)
{
    if (m_alignmentMode != mode)
    {
        m_alignmentMode = mode;
        m_needsLayout   = true;
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
    Vec2  newPos;
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

    switch (m_alignmentMode)
    {
        case AlignMode::Left:
            xPos = m_position.x + m_offset + prefixWidth;
            break;
        case AlignMode::Middle:
        {
            float startX = m_position.x + (m_width / 2.0f) - (totalWidth / 2.0f);
            xPos         = startX + prefixWidth;
        }
        break;
        case AlignMode::Right:
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

bool Container::wantsGetInput() const
{
    for (const auto& widget : m_subWidgets)
    {
        if (widget->wantsGetInput()) return true;
    }
    return false;
}

void Container::passInput(unsigned int codepoint)
{
    for (auto& subWidget : m_subWidgets)
    {
        if (!subWidget->wantsGetInput()) continue;

        subWidget->passInput(codepoint);
    }
}

void Container::handleHover(double x, double y)
{
    bool foundHover = false;

    for (auto& subWidget : m_subWidgets)
    {
        if (!subWidget->wantsHoverEvents())
        {
            subWidget->resetHover();
            continue;
        }

        if (!foundHover && subWidget->isInside(x, y))
        {
            subWidget->handleHover(x, y);
            foundHover = true;
        }
        else
        {
            subWidget->resetHover();
        }
    }
}

void Container::resetHover()
{
    for (auto& subWidget : m_subWidgets)
    {
        subWidget->resetHover();
    }
}

}  // namespace Optikos