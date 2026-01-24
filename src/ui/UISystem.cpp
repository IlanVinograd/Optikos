#include "ui/UISystem.hpp"

bool UISystem::add_widget(const uint32_t idx, std::unique_ptr<IWidget> widget)
{
    auto [it, inserted] = widgets.try_emplace(idx, std::move(widget));

    if (!inserted)
    {
        LOG_ERROR("[add_widget] widget with idx: " + std::to_string(idx) + " not added", "log");
        return false;
    }

    return true;
}

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
        if (widget->isExpand())
        {
            widget->resize(width, height);
        }
    }
}