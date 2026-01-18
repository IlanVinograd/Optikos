#include "ui/UISystem.hpp"

bool UISystem::add_widget(const uint32_t idx, IWidget* widget)
{
    auto [it, inserted] = widgets.try_emplace(idx, widget);

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