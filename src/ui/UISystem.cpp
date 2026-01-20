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

RenderData UISystem::accumulateWidgets()
{
    RenderData data;
    for (const auto& widget : widgets)
    {
        auto dataVertices = widget.second->getVertices();
        auto dataIndices = widget.second->getIndices();

        data.vertices.insert(data.vertices.end(), dataVertices.begin(), dataVertices.end());
        data.indices.insert(data.indices.end(), dataIndices.begin(), dataIndices.end());
    }
    return data;
}