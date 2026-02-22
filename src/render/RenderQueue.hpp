#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

#include "render/IRenderQueue.hpp"

namespace Optikos
{
class RenderQueue final : public IRenderQueue
{
   public:
    void                             submit(const DrawCommand&& command) override;
    void                             clear() override;
    const std::vector<DrawCommand>&  getCommands() const override;
    inline std::vector<DrawCommand>& getMutableCommands()
    {
        return m_commands;
    }

   private:
    std::vector<DrawCommand> m_commands;
};
}  // namespace Optikos

#endif /* RENDERQUEUE_H */