#ifndef UISYSTEM_H
#define UISYSTEM_H

#include <memory>
#include <unordered_map>

#include "render/IRenderQueue.hpp"
#include "ui/IWidget.hpp"
#include "utilities/logger.hpp"


class UISystem
{
   public:
    UISystem() = default;

    template <typename T>
    T* add_widget(const uint32_t idx, std::unique_ptr<T> widget)
    {
        auto* ptr           = widget.get();
        auto [it, inserted] = widgets.try_emplace(idx, std::move(widget));

        if (!inserted)
        {
            LOG_ERROR("[add_widget] widget with idx: " + std::to_string(idx) + " not added", "log");
            return nullptr;
        }

        return ptr;
    }

    bool rem_widget(const uint32_t idx);

    void checkIfClicked(double x, double y);

    void checkIfHover(double x, double y);

    void expandWidgets(int width, int height);

    void render(Optikos::IRenderQueue& renderQueue);

   private:
    std::unordered_map<uint32_t, std::unique_ptr<IWidget>> widgets;

    bool isInside(const IWidget& widget, double x, double y);
};

#endif /* UISYSTEM_H */