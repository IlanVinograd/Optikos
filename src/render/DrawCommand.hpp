#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H

#include <vector>

struct Vertex
{
    float         x, y;
    unsigned char r, g, b, a;
    float         u, v;
    float         fw, tw, fh, th;
};

namespace Optikos
{
struct DrawCommand
{
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    unsigned int              shaderId;
    unsigned int              textureId;
};
}  // namespace Optikos

#endif /* DRAWCOMMAND_H */