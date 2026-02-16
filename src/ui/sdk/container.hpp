#ifndef CONTAINER_H
#define CONTAINER_H

#include <type_traits>

#include "ui/Widget.hpp"

namespace Optikos
{
enum class AlignMode : uint8_t
{
    Left   = 0,
    Middle = 1,
    Right  = 2
};

class Container : public Widget
{
   public:
    Container(uint32_t width, uint32_t height, Vec2 position, Color color = {0, 0, 0, 1},
              bool isVisible = true);  // simple rectangle container

    void                             render(IRenderQueue& renderQueue) override;
    void                             updateData() override;
    const std::vector<float>&        getVertices() const override;
    const std::vector<unsigned int>& getIndices() const override;
    void                             handleEvent() override;
    bool                             handleClick(double x, double y) override;
    void                             handleHover(double x, double y) override;
    void                             resetHover() override;
    bool                             wantsHoverEvents() const override;
    bool                             wantsGetInput() const override;
    void                             passInput(unsigned int codepoint) override;
    void                             resize(int width, int height) override;
    void                             setPosition(Vec2 pos) override;

    template <typename T>
    T* addSubWidget(std::unique_ptr<T> widget)
    {
        T* subWidget = widget.get();
        if constexpr (std::is_same_v<T, Container>)
        {
            if (this != subWidget)
            {
                m_subWidgets.push_back(std::move(widget));
                m_needsLayout = true;
            }
            else
                LOG_DEBUG("addSubWidget add [this] to [this]", "log");
        }
        else
        {
            m_subWidgets.push_back(std::move(widget));
            m_needsLayout = true;
        }
        return subWidget;
    }
    void setAlignment(AlignMode mode);
    void setInterval(int interval);
    void setOffset(int offset);

   private:
    void alignWidget(IWidget* subWidget, int i);
    void updateLayout();

    RenderData                            m_data;
    AlignMode                             m_alignmentMode = AlignMode::Left;
    int                                   m_offset        = 0;
    int                                   m_interval      = 0;
    bool                                  m_needsLayout   = true;
    std::vector<std::unique_ptr<IWidget>> m_subWidgets;
};

}  // namespace Optikos

#endif /* CONTAINER_H */