#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <string>

#include "ui/sdk/container.hpp"
#include "ui/sdk/label.hpp"

#define BACKSPACE 259
#define KEY_RIGHT 262
#define KEY_LEFT 263
#define DELETE 261

namespace Optikos
{
class TextBox : public Container
{
   public:
    TextBox(uint32_t width, uint32_t height, Vec2 position,
            Color bgColor   = {50.0, 50.0, 50.0, 255.0},
            Color textColor = {255.0, 255.0, 255.0, 255.0});

    void render(IRenderQueue& renderQueue) override;
    void updateData() override;
    void handleEvent() override;
    bool handleClick(double x, double y) override;
    void handleHover(double x, double y) override;
    void resetHover() override;
    bool wantsHoverEvents() const override;
    bool wantsGetInput() const override;
    void passInput(unsigned int codepoint) override;
    void resize(int width, int height) override;
    void setPosition(Vec2 pos) override;

    const std::vector<float>&        getVertices() const override;
    const std::vector<unsigned int>& getIndices() const override;

    void        setText(const std::string& text);
    std::string getText() const;
    void        setTextColor(Color color);
    void        setFont(const std::string& font);
    void        setPlaceholder(const std::string& placeholder);
    void        setFocused(bool focused);
    bool        isFocused() const;

   private:
    void handleCursor(double x, double y);

    RenderData  m_data;
    int         m_cursorEnd;
    int         m_cursorPivot;
    std::string m_text;
    std::string m_placeholder;
    std::string m_fontName = DEFAULT0_FONT;
    Color       m_textColor;
    Color       m_bgColor;
    Color       m_focusedBgColor;
    Color       m_hoverBgColor;
    Label*      m_label   = nullptr;
    bool        m_focused = false;
    bool        m_isHover = false;
};

}  // namespace Optikos

#endif /* TEXTBOX_H */