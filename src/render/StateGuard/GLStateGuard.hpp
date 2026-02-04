#ifndef GLSTATEGUARD_H
#define GLSTATEGUARD_H

#include "render/StateGuard/IStateGuard.hpp"

class GLStateGuard : IStateGuard
{
   public:
    void acquire() override;
    void release() override;
};

#endif /* GLSTATEGUARD_H */