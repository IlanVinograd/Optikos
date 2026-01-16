#ifndef IWINDOW_H
#define IWINDOW_H

namespace Optikos {

enum class GraphicsAPI {
    None,
    OpenGL,
    // Vulkan,
    // DirectX12
};

struct GraphicsConfig {
    GraphicsAPI api = GraphicsAPI::OpenGL;
    int versionMajor = 4;
    int versionMinor = 6;
};

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
    virtual bool should_close() const = 0;

private:
    
};

} /* Optikos */

#endif /* IWINDOW_H */