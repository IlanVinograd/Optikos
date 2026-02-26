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

int constexpr TEXTURE_NONE = 0;
int constexpr TEXTURE_FONT = 1;
int constexpr TEXTURE_IMG  = 2;

struct DrawCommand
{
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    unsigned int              shaderId;
    unsigned int              textureId;
    int                       textureMode = TEXTURE_NONE;
};
}  // namespace Optikos

#endif /* DRAWCOMMAND_H */