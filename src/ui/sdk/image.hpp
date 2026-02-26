#ifndef IMAGE_H
#define IMAGE_H

#include "ui/Widget.hpp"

namespace Optikos
{

using OpTextureID = unsigned long long;

class Image : public Widget
{
   public:
    Image(OpTextureID id, uint32_t width, uint32_t height, Vec2 position);

    void                             render(IRenderQueue& renderQueue) override;
    void                             updateData() override;
    const std::vector<Vertex>&       getVertices() const override;
    const std::vector<unsigned int>& getIndices() const override;
    void                             resize(int width, int height) override;
    void                             setPosition(Vec2 pos) override;
    void                             handleEvent() override;

    void setTexture(OpTextureID id);

   private:
    RenderData  m_data;
    OpTextureID m_id;

    bool m_needUpdate;
};

}  // namespace Optikos

#endif /* IMAGE_H */