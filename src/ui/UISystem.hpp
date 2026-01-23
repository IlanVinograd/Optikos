#ifndef UISYSTEM_H
#define UISYSTEM_H

#include <memory>
#include <unordered_map>

#include "ui/IWidget.hpp"
#include "render/IRenderQueue.hpp"

#include "utilities/logger.hpp"

class UISystem
{
   public:
    UISystem() = default;

    bool add_widget(const uint32_t idx, std::unique_ptr<IWidget> widget);
    bool rem_widget(const uint32_t idx);

    void checkIfClicked(double x, double y);

    void render(Optikos::IRenderQueue& renderQueue);

   private:
    std::unordered_map<uint32_t, std::unique_ptr<IWidget>> widgets;

    bool isInside(const IWidget& widget, double x, double y);
};

#endif /* UISYSTEM_H */