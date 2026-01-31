#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H

#include <vector>

namespace Optikos
{
struct DrawCommand
{
    std::vector<float>        vertices;
    std::vector<unsigned int> indices;
    unsigned int              shaderId;
    unsigned int              textureId;
};
}  // namespace Optikos

#endif /* DRAWCOMMAND_H */