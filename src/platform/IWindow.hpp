#ifndef IWINDOW_H
#define IWINDOW_H

namespace Optikos
{
class IRenderer;

enum class GraphicsAPI
{
    None,
    OpenGL,
    // Vulkan,
    // DirectX12
};

struct GraphicsConfig
{
    GraphicsAPI api          = GraphicsAPI::OpenGL;
    int         versionMajor = 4;
    int         versionMinor = 6;
};

struct Color
{
    float r;
    float g;
    float b;
};

struct Window
{
    int height;
    int width;
};

class IWindow
{
   public:
    virtual ~IWindow()                             = default;
    virtual void  setWindowTitleBar(Color color)   = 0;
    virtual void  setRenderer(IRenderer* renderer) = 0;
    virtual void* native_handle()                  = 0;
    virtual void  poll_events()                    = 0;
    virtual bool  should_close() const             = 0;
    virtual int   getHeight() const                = 0;
    virtual int   getWidth() const                 = 0;

   private:
};

}  // namespace Optikos

#endif /* IWINDOW_H */