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

void Container::render(Optikos::IRenderQueue& renderQueue)
{
    IWidget::render(renderQueue);
    updateLayout();
    for (auto& subWidget : m_subWidgets)
    {
        subWidget->render(renderQueue);
    }
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
        handleEvent();
        return true;
    }

    return false;
}

vec2 Container::getPosition() const
{
    return m_attributes.position;
}

void Container::setPosition(vec2 pos)
{
    m_attributes.position = pos;

    m_data.vertices = {pos.x,
                       pos.y,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,
                       pos.x + m_attributes.width,
                       pos.y,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,
                       pos.x + m_attributes.width,
                       pos.y + m_attributes.height,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,
                       pos.x,
                       pos.y + m_attributes.height,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a};

    m_needsLayout = true;
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

void Container::setClickable(bool isClickable)
{
    m_attributes.isClickable = isClickable;
}

bool Container::getClickable() const
{
    return m_attributes.isClickable;
}

void Container::resize(int width, int height)
{
    m_attributes.width  = width;
    m_attributes.height = height;

    m_data.vertices = {m_attributes.position.x,
                       m_attributes.position.y,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,

                       m_attributes.position.x + width,
                       m_attributes.position.y,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,

                       m_attributes.position.x + width,
                       m_attributes.position.y + height,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a,

                       m_attributes.position.x,
                       m_attributes.position.y + height,
                       m_color.r,
                       m_color.g,
                       m_color.b,
                       m_color.a};

    m_needsLayout = true;
}

void Container::handleEvent()
{
    std::cout << "clicked" << std::endl;
    return; /* stub */
}

void Container::setAutoExpand(int isExpand)
{
    assert(isExpand >= 0 && isExpand <= 3);
    /* 0 = don't expand, 1 = expand only width, 2 = expand only height, 3 = expand both */ //TODO: make enums/defines

    m_attributes.isExpand = isExpand;
}

int Container::isExpand()
{
    return m_attributes.isExpand;
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
    /* 0 = from left, 1 = middle, 2 = from right */ //TODO: make enums/defines
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
    //TODO: need optimization
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
            xPos = m_attributes.position.x + m_offset + prefixWidth;
            break;
        case 1:
        {
            float startX =
                m_attributes.position.x + (m_attributes.width / 2.0f) - (totalWidth / 2.0f);
            xPos = startX + prefixWidth;
        }
        break;
        case 2:
        {
            float startX = m_attributes.position.x + m_attributes.width - totalWidth - m_offset;
            xPos         = startX + prefixWidth;
        }
        break;
        default:
            xPos = m_attributes.position.x + m_offset + prefixWidth;
            break;
    }

    newPos = {xPos, m_attributes.position.y};
    subWidget->setPosition(newPos);
}