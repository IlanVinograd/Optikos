#include "ui/UISystem.hpp"

bool UISystem::rem_widget(const uint32_t idx)
{
    auto it = widgets.find(idx);
    if (it != widgets.end())
    {
        widgets.erase(idx);
        return true;
    }

    LOG_ERROR("[rem_widget] widget with idx: " + std::to_string(idx) + " not removed", "log");
    return false;
}

void UISystem::render(Optikos::IRenderQueue& renderQueue)
{
    for (const auto& [id, widget] : widgets)
    {
        if (widget->getVisible())
        {
            Optikos::DrawCommand cmd;
            cmd.vertices = widget->getVertices();
            cmd.indices  = widget->getIndices();
            cmd.shaderId = 0;

            renderQueue.submit(std::move(cmd));
        }
    }
}

void UISystem::checkIfClicked(double x, double y)
{
    for (const auto& [id, widget] : widgets)
    {
        if (widget->getVisible() && isInside(*widget, x, y))
        {
            widget->handleEvent();
        }
    }
}

bool UISystem::isInside(const IWidget& widget, double x, double y)
{
    vec2 widgetPos = widget.getPosition();
    if (widgetPos.x <= x && x <= widgetPos.x + widget.getWidth() && widgetPos.y <= y &&
        y <= widgetPos.y + widget.getHeight())
        return true;

    return false;
}

void UISystem::expandWidgets(int width, int height)
{
    for (auto& [id, widget] : widgets)
    {
        switch (widget->isExpand())
        {
            case 0:
                break;
            case 1:
                widget->resize(width, widget->getHeight());
                break;
            case 2:
                widget->resize(widget->getWidth(), height);
                break;
            case 3:
                widget->resize(width, height);
                break;
            default:
                LOG_WARN(
                    "[expandWidgets] Invalid expand mode: " + std::to_string(widget->isExpand()),
                    "log");
                break;
        }
    }
}