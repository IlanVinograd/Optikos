#ifndef UISYSTEM_H
#define UISYSTEM_H

#include <memory>
#include <unordered_map>

#include "render/IRenderQueue.hpp"
#include "ui/IWidget.hpp"
#include "utilities/logger.hpp"

namespace Optikos
{
class UISystem
{
   public:
    UISystem() = default;

    template <typename T>
    T* add_widget(const uint32_t idx, std::unique_ptr<T> widget)
    {
        auto [it, inserted] = widgets.try_emplace(idx, std::move(widget));

        if (!inserted)
        {
            LOG_ERROR("[add_widget] widget with idx: " + std::to_string(idx) + " not added", "log");
            return nullptr;
        }

        return static_cast<T*>(it->second.get());
    }

    bool rem_widget(const uint32_t idx);

    void checkIfClicked(double x, double y, int action);

    void checkIfHover(double x, double y);

    void expandWidgets(int width, int height);

    void render(IRenderQueue& renderQueue);

    void passInput(unsigned int codepoint);

   private:
    std::unordered_map<uint32_t, std::unique_ptr<IWidget>> widgets;

    bool isInside(const IWidget& widget, double x, double y);
};

}  // namespace Optikos

#endif /* UISYSTEM_H */