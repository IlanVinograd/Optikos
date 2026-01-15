#ifndef IRENDER_H
#define IRENDER_H

namespace Optikos {

class IRenderer {
public:
    virtual ~IRenderer() = default;
    virtual void swap_buffer() = 0;

private:

};

} /* Optikos */

#endif /* IRENDER_H */