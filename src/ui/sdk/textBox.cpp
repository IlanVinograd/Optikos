#include "ui/sdk/textBox.hpp"

namespace Optikos
{
TextBox::TextBox(uint32_t width, uint32_t height, Vec2 position, Color bgColor, Color textColor)
    : Container(width, height, position, bgColor, true),
      m_textColor(textColor),
      m_bgColor(bgColor),
      m_focusedBgColor(std::min(bgColor.r * 1.2f, 255.0f), std::min(bgColor.g * 1.2f, 255.0f),
                       std::min(bgColor.b * 1.2f, 255.0f), bgColor.a),
      m_hoverBgColor(std::min(bgColor.r * 1.1f, 255.0f), std::min(bgColor.g * 1.1f, 255.0f),
                     std::min(bgColor.b * 1.1f, 255.0f), bgColor.a)
{
    m_label = addSubWidget(std::make_unique<Label>("", Vec2(0, 0), 0, 0, m_textColor));

    updateData();

    m_isClickable = true;
}

void TextBox::render(IRenderQueue& renderQueue)
{
    if (!m_isVisible) return;

    DrawCommand bgCmd;
    bgCmd.vertices  = m_data.vertices;
    bgCmd.indices   = m_data.indices;
    bgCmd.shaderId  = 0;
    bgCmd.textureId = 0;
    renderQueue.submit(std::move(bgCmd));

    if (m_label)
    {
        if (m_focused)
        {
            std::string modified = m_placeholder;
            m_label->setText(modified.insert(m_cursorEnd, "|"));
            m_label->setFont(m_fontName);
        }
        else
        {
            m_label->setText(m_text);
            m_label->setFont(m_fontName);
        }

        m_label->render(renderQueue);
    }
}

void TextBox::updateData()
{
    Color currentColor = m_bgColor;
    if (m_focused)
        currentColor = m_focusedBgColor;
    else if (m_isHover)
        currentColor = m_hoverBgColor;

    m_data.indices  = {0, 1, 2, 2, 3, 0};
    m_data.vertices = {m_position.x,
                       m_position.y,
                       currentColor.r,
                       currentColor.g,
                       currentColor.b,
                       currentColor.a,
                       0.0f,
                       0.0f,

                       m_position.x + m_width,
                       m_position.y,
                       currentColor.r,
                       currentColor.g,
                       currentColor.b,
                       currentColor.a,
                       0.0f,
                       0.0f,

                       m_position.x + m_width,
                       m_position.y + m_height,
                       currentColor.r,
                       currentColor.g,
                       currentColor.b,
                       currentColor.a,
                       0.0f,
                       0.0f,

                       m_position.x,
                       m_position.y + m_height,
                       currentColor.r,
                       currentColor.g,
                       currentColor.b,
                       currentColor.a,
                       0.0f,
                       0.0f};

    if (m_label)
    {
        m_label->setPosition(Vec2{m_position.x + 5, m_position.y});
        m_label->resize(m_width - 10, m_height);
        m_label->setText(m_text);
    }
}

void TextBox::handleEvent()
{
    if (!m_focused)
    {
        m_placeholder = m_text;
        m_cursorPivot = 0;  // for selection curretnly not used
        m_cursorEnd   = (int) m_text.length();
        setFocused(true);
    }
}

bool TextBox::handleClick(double x, double y)
{
    if (m_isClickable && isInside(x, y))
    {
        handleEvent();
        if (m_focused) handleCursor(x, y);
        return true;
    }
    else if (m_focused)
    {
        m_text = m_placeholder;
        m_placeholder.clear();
        setFocused(false);
    }
    return false;
}

void TextBox::handleHover(double x, double y)
{
    (void) x;
    (void) y;

    if (!m_isHover)
    {
        m_isHover = true;
        updateData();
    }
}

void TextBox::resetHover()
{
    if (m_isHover)
    {
        m_isHover = false;
        updateData();
    }
}

bool TextBox::wantsHoverEvents() const
{
    return true;
}

bool TextBox::wantsGetInput() const
{
    return m_focused;
}

void TextBox::passInput(unsigned int codepoint)
{
    // TODO: to seperate func for manageCursor
    // TODO: Add define for range
    if (32 <= codepoint && codepoint <= 126)
    {
        m_placeholder.insert(m_cursorEnd, 1, static_cast<unsigned char>(codepoint));
        m_cursorEnd++;
    }
    else if (m_cursorEnd > 0 && codepoint == BACKSPACE)
    {
        m_cursorEnd--;
        m_placeholder.erase(m_cursorEnd, 1);
    }
    else if (m_cursorEnd < m_placeholder.length() && codepoint == DELETE)
    {
        m_placeholder.erase(m_cursorEnd, 1);
    }
    else if (m_cursorEnd > 0 && codepoint == KEY_LEFT)
    {
        m_cursorEnd--;
    }
    else if (m_cursorEnd < m_placeholder.length() && codepoint == KEY_RIGHT)
    {
        m_cursorEnd++;
    }
    else
    {
        /* stub */
    }
    std::cout << m_placeholder.length() << std::endl;
    std::cout << m_cursorEnd << std::endl;

    updateData();
}

void TextBox::resize(int width, int height)
{
    m_width  = width;
    m_height = height;
    updateData();
}

void TextBox::setPosition(Vec2 pos)
{
    m_position = pos;
    updateData();
}

const std::vector<float>& TextBox::getVertices() const
{
    return m_data.vertices;
}

const std::vector<unsigned int>& TextBox::getIndices() const
{
    return m_data.indices;
}

void TextBox::setText(const std::string& text)
{
    m_text = text;
    updateData();
}

std::string TextBox::getText() const
{
    return m_text;
}

void TextBox::setTextColor(Color color)
{
    m_textColor = color;
    if (m_label)
    {
        m_label->setColor(color);
    }
}

void TextBox::setFont(const std::string& font)
{
    m_fontName = font;
    if (m_label)
    {
        m_label->setFont(font);
    }
}

void TextBox::setPlaceholder(const std::string& placeholder)
{
    m_placeholder = placeholder;
}

void TextBox::setFocused(bool focused)
{
    m_focused = focused;
    updateData();
}

bool TextBox::isFocused() const
{
    return m_focused;
}

void TextBox::handleCursor(double x, double y)  // ABCD = 4 -> AB CD , if m_focused true only
{
    // TODO: OPTIMIZE CURSOR CLICK POSITION
    Vec2   textSize = TextFont::getInstance().getSizeText(m_placeholder, m_fontName);
    double xTextPos = (m_width / 2) - (textSize.x / 2) + m_position.x;
    m_cursorEnd     = TextFont::getInstance().getPosText(x - xTextPos, m_placeholder, m_fontName);

    std::cout << x - xTextPos << std::endl;
    std::cout << textSize.x << " " << x << " " << xTextPos << " " << m_cursorEnd << std::endl;

    (void) xTextPos;
    (void) x;
    (void) y;
}

}  // namespace Optikos