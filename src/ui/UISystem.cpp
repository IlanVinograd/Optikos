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
        widget->render(renderQueue);
    }
}

void UISystem::checkIfClicked(double x, double y)
{
    for (const auto& [id, widget] : widgets)
    {
        if (widget->handleClick(x, y))
        {
            return;
        }
    }
}

void UISystem::checkIfHover(double x, double y)
{
    for (const auto& [id, widget] : widgets)
    {
        if (!widget->wantsHoverEvents()) continue;

        if (widget->isInside(x, y))
            widget->handleHover(x, y);
        else
            widget->resetHover();
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
            case ExpandMode::None:
                break;
            case ExpandMode::Width:
                widget->resize(width, widget->getHeight());
                break;
            case ExpandMode::Height:
                widget->resize(widget->getWidth(), height);
                break;
            case ExpandMode::Both:
                widget->resize(width, height);
                break;
            default:
                LOG_WARN(
                    "[expandWidgets] Invalid expand mode: " + std::to_string(static_cast<int>(widget->isExpand())),
                    "log");
                break;
        }
    }
}