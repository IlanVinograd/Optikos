#ifndef IWINDOW_H
#define IWINDOW_H

namespace Optikos {

struct Color {
    int r;
    int g;
    int b;
};

class IWindow {
public:
    virtual ~IWindow() = default;
    virtual void setWindowTitleBar(Color color) = 0;
    virtual void* native_handle() = 0;
    virtual void poll_events() = 0;

private:
    
};

} /* Optikos */

#endif /* IWINDOW_H */