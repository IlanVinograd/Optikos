#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include <iostream>

#include "platform/glfw/GLFWWindow.hpp"
#include "render/IRenderer.hpp"
#include "utilities/logger.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Optikos
{
class OpenGLRenderer : public IRenderer
{
   public:
    explicit OpenGLRenderer(IWindow* window, UISystem* uiSystem);
    virtual ~OpenGLRenderer() override = default;

    void swap_buffer() override;
    void onWindowResize(int width, int height) override;

   private:
    IWindow*  m_window;
    UISystem* m_uiSystem;
};

}  // namespace Optikos

#endif /* OPENGLRENDERER_H */