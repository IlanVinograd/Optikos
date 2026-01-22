#ifndef IRENDERQUEUE_H
#define IRENDERQUEUE_H

#include "render/DrawCommand.hpp"

namespace Optikos
{
class IRenderQueue
{
   public:
    virtual ~IRenderQueue() = default;

    virtual void                            submit(const DrawCommand&& command) = 0;
    virtual void                            clear()                            = 0;
    virtual const std::vector<DrawCommand>& getCommands() const                = 0;
};
}  // namespace Optikos

#endif /* IRENDERQUEUE_H */