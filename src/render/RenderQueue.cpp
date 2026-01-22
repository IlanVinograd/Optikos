#include "render/RenderQueue.hpp"

namespace Optikos
{

void RenderQueue::submit(const DrawCommand&& command)
{
    m_commands.push_back(command);
}

void RenderQueue::clear()
{
    m_commands.clear();
}

const std::vector<DrawCommand>& RenderQueue::getCommands() const
{
    return m_commands;
}

}  // namespace Optikos