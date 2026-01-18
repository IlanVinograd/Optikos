#ifndef IRENDER_H
#define IRENDER_H

#include "ui/UISystem.hpp"

namespace Optikos
{
class IRenderer
{
   public:
    virtual ~IRenderer()                               = default;
    virtual void onWindowResize(int width, int height) = 0;
    virtual void swap_buffer()                         = 0;

   private:
};

}  // namespace Optikos

#endif /* IRENDER_H */