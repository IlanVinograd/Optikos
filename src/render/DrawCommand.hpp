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
};
}  // namespace Optikos

#endif /* DRAWCOMMAND_H */